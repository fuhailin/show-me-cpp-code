/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <algorithm>
#include <vector>

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/nn_ops.h"
#include "tensorflow/cc/ops/nn_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"

#include "tensorflow/examples/cc/gan/pix2pix/const.h"
#include "tensorflow/examples/cc/gan/pix2pix/function.h"
#include "tensorflow/examples/cc/gan/pix2pix/model.h"

namespace tensorflow {
namespace ops {

Output DiscriminatorLoss(const Scope& scope, const Input& real_output,
                         const Input& fake_output) {
  auto real_loss =
      ReduceMean(scope,
                 SigmoidCrossEntropyWithLogits(
                     scope, OnesLike(scope, real_output), real_output),
                 {0, 1});
  auto fake_loss =
      ReduceMean(scope,
                 SigmoidCrossEntropyWithLogits(
                     scope, ZerosLike(scope, fake_output), fake_output),
                 {0, 1});

  return Add(scope, real_loss, fake_loss);
}

Output GeneratorLoss(const Scope& scope, const Input& fake_output) {
  auto fake_loss =
      ReduceMean(scope,
                 SigmoidCrossEntropyWithLogits(
                     scope, OnesLike(scope, fake_output), fake_output),
                 {0, 1});

  return fake_loss;
}

std::tuple<Output, Output> LoadP2P(const Scope& scope,
                                   const Output& image_file) {
  auto read_file = ReadFile(scope, image_file);
  auto image = DecodeJpeg(scope, read_file);
  auto shape = Shape(scope, image);
  Output w = StridedSlice(scope, shape, {1}, {2}, {1});
  Output w1 = Div(scope, w, 2);
  LOG(INFO) << "Node building status: " << scope.status();

  auto stack =
      Stack(scope, {Const(scope, {IMAGE_SIZE}), w1, Const(scope, {3})});
  auto pos = Reshape(scope, stack, {3});
  LOG(INFO) << "Node building status: " << scope.status();

  auto stack2 = Stack(scope, {Const(scope, {0}), w1, Const(scope, {0})});
  auto pos2 = Reshape(scope, stack2, {3});
  LOG(INFO) << "Node building status: " << scope.status();

  auto stack3 =
      Stack(scope, {Const(scope, {IMAGE_SIZE}), w, Const(scope, {3})});
  auto pos3 = Reshape(scope, stack3, {3});
  LOG(INFO) << "Node building status: " << scope.status();

  auto real_image = Cast(
      scope, StridedSlice(scope, image, {0, 0, 0}, pos, {1, 1, 1}), DT_FLOAT);
  LOG(INFO) << "Node building status: " << scope.status();

  auto input_image =
      Cast(scope, StridedSlice(scope, image, pos2, pos3, {1, 1, 1}), DT_FLOAT);
  LOG(INFO) << "Node building status: " << scope.status();

  return std::make_tuple(input_image, real_image);
}

std::tuple<Output, Output> ResizeP2P(const Scope& scope,
                                     const Output& input_image,
                                     const Output& real_image, const int height,
                                     const int width) {
  auto ret_input_image = ResizeBilinear(
      scope, Reshape(scope, input_image, {1, IMAGE_SIZE, IMAGE_SIZE, 3}),
      {height, width});
  auto ret_real_image = ResizeBilinear(
      scope, Reshape(scope, real_image, {1, IMAGE_SIZE, IMAGE_SIZE, 3}),
      {height, width});
  LOG(INFO) << "Node building status: " << scope.status();

  return std::make_tuple(ret_input_image, ret_real_image);
}

std::tuple<Output, Output> RandomCropP2P(const Scope& scope,
                                         const Output& input_image,
                                         const Output& real_image) {
  // tensorflow::int64 size = IMAGE_SIZE;
  // auto ret_input_image = RandomCrop(scope, Reshape(scope, input_image,
  // {RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE, 3}), {size, size}); auto
  // ret_real_image = RandomCrop(scope, Reshape(scope, real_image,
  // {RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE, 3}), {size, size});

  // Actually no need
  auto shape = Shape(
      scope,
      Reshape(scope, input_image, {RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE, 3}));

  auto limit = Add(scope, Subtract(scope, shape, {IMAGE_SIZE, IMAGE_SIZE, 3}),
                   {1, 1, 1});
  auto offset = Mod(
      scope, RandomUniformInt(scope, Shape(scope, limit), 0, INT32_MAX), limit);
  LOG(INFO) << "Node building status: " << scope.status();

  auto ret_input_image = Slice(
      scope,
      Reshape(scope, input_image, {RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE, 3}),
      offset, {IMAGE_SIZE, IMAGE_SIZE, 3});
  auto ret_real_image = Slice(
      scope,
      Reshape(scope, real_image, {RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE, 3}),
      offset, {IMAGE_SIZE, IMAGE_SIZE, 3});
  LOG(INFO) << "Node building status: " << scope.status();

  return std::make_tuple(ret_input_image, ret_real_image);
}

std::tuple<Output, Output> NormalizeP2P(const Scope& scope,
                                        const Output& input_image,
                                        const Output& real_image) {
  auto ret_input_image = Subtract(scope, Div(scope, input_image, 127.5f), 1.0f);
  auto ret_real_image = Subtract(scope, Div(scope, real_image, 127.5f), 1.0f);
  LOG(INFO) << "Node building status: " << scope.status();

  return std::make_tuple(ret_input_image, ret_real_image);
}

std::tuple<Output, Output> RandomJitterP2P(const Scope& scope,
                                           const Output& input_image,
                                           const Output& real_image) {
  Output ret_input_image;
  Output ret_real_image;
  std::tie(ret_input_image, ret_real_image) = ResizeP2P(
      scope, input_image, real_image, RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE);
  std::tie(ret_input_image, ret_real_image) =
      RandomCropP2P(scope, ret_input_image, ret_real_image);

  auto const0 = Const<float>(scope, 0.5f, TensorShape({}));
  auto random_value = RandomUniform(scope, Shape(scope, const0), DT_FLOAT);
  LOG(INFO) << "Node building status: " << scope.status();
  ret_input_image =
      Where3(scope, Greater(scope, random_value, const0),
             Reverse(scope, ret_input_image, {1}), ret_input_image);
  ret_real_image = Where3(scope, Greater(scope, random_value, const0),
                          Reverse(scope, ret_real_image, {1}), ret_real_image);
  LOG(INFO) << "Node building status: " << scope.status();

  return std::make_tuple(ret_input_image, ret_real_image);
}

std::tuple<Output, Output> LoadImageTrainX(const Scope& scope,
                                           const Output& image_file) {
  Output ret_input_image;
  Output ret_real_image;
  std::tie(ret_input_image, ret_real_image) = LoadP2P(scope, image_file);
  std::tie(ret_input_image, ret_real_image) =
      RandomJitterP2P(scope, ret_input_image, ret_real_image);
  std::tie(ret_input_image, ret_real_image) =
      NormalizeP2P(scope, ret_input_image, ret_real_image);

  return std::make_tuple(ret_input_image, ret_real_image);
}

Output LoadImageTrain(const Scope& scope, const Output& image_file) {
  Output ret_input_image;
  Output ret_real_image;
  std::tie(ret_input_image, ret_real_image) = LoadP2P(scope, image_file);
  std::tie(ret_input_image, ret_real_image) =
      RandomJitterP2P(scope, ret_input_image, ret_real_image);
  std::tie(ret_input_image, ret_real_image) =
      NormalizeP2P(scope, ret_input_image, ret_real_image);
  auto ret = Stack(scope, {ret_input_image, ret_real_image});

  return ret;
}

std::tuple<Output, Output> LoadImageTestX(const Scope& scope,
                                          const Output& image_file) {
  Output ret_input_image;
  Output ret_real_image;
  std::tie(ret_input_image, ret_real_image) = LoadP2P(scope, image_file);
  std::tie(ret_input_image, ret_real_image) =
      ResizeP2P(scope, ret_input_image, ret_real_image, IMAGE_SIZE, IMAGE_SIZE);
  std::tie(ret_input_image, ret_real_image) =
      NormalizeP2P(scope, ret_input_image, ret_real_image);

  return std::make_tuple(ret_input_image, ret_real_image);
}

Output LoadImageTest(const Scope& scope, const Output& image_file) {
  Output ret_input_image;
  Output ret_real_image;
  std::tie(ret_input_image, ret_real_image) = LoadP2P(scope, image_file);
  std::tie(ret_input_image, ret_real_image) =
      ResizeP2P(scope, ret_input_image, ret_real_image, IMAGE_SIZE, IMAGE_SIZE);
  std::tie(ret_input_image, ret_real_image) =
      NormalizeP2P(scope, ret_input_image, ret_real_image);

  auto ret = Stack(scope, {ret_input_image, ret_real_image});

  return ret;
}

}  // namespace ops
}  // namespace tensorflow
