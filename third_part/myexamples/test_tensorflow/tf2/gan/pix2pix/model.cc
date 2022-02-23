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
#include "tensorflow/examples/cc/gan/pix2pix/model.h"

namespace tensorflow {
namespace ops {

Output DownSample(const ::tensorflow::Scope& scope, const Output& inputs, 
                  const int filter, const int size, 
                  const bool apply_batchnorm, const bool training) {
  auto weight = TFVariable(scope.WithOpName("weight"),
                                   {size, size, NUM_CHANNELS, filter}, DT_FLOAT, true);

  auto rate = Const(scope, {0.02f});
  auto random_value = RandomNormal(scope, {size, size, NUM_CHANNELS, filter}, DT_FLOAT);
  TFAssign(scope, weight, Multiply(scope, random_value, rate));

  // Convnet
  Output conv2d = Conv2D(scope, inputs, weight,
                         gtl::ArraySlice<int>{1, 2, 2, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  if(apply_batchnorm) {
    auto batchnorm_op = TFFusedBatchNorm(scope, {filter});
    conv2d = batchnorm_op.Build(scope, conv2d, 0.001f, training);
    LOG(INFO) << "Node building status: " << scope.status();
  }

  auto relu =
      internal::LeakyRelu(scope, conv2d,
                          internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  return relu;
}

Output UpSample(const ::tensorflow::Scope& scope, 
                const Input& input, const TensorShape& input_shape, 
                const int filter, const int size, const int batch_size, 
                const bool apply_dropout, const bool training) {
  // filters shape => kernel_shape = self.kernel_size + (self.filters, input_dim)
  //   self.kernel_size is {size, size}
  //   self.filters is "const int filter"
  //   input_dim is inputs_shape[-1]
  //
  int input_dim = input_shape.dim_size(3);
  auto filtersVar = TFVariable(scope.WithOpName("filters"),
                                   {size, size, filter, input_dim}, DT_FLOAT, true);

  auto rate = Const(scope, {0.02f});
  auto random_value = RandomNormal(scope, {size, size, filter, input_dim}, DT_FLOAT);
  TFAssign(scope, filtersVar, Multiply(scope, random_value, rate));

  // input_sizes => output_shape = (batch_size, out_height, out_width, self.filters)
  //   for "same", out_height = inputs_shape[1] * stride_h, 
  //               out_width = inputs_shape[2] * stride_h
  //               self.filters is "const int filter"
  //
  const int stride_h = 2;
  const int stride_w = 2;
  int out_height = input_shape.dim_size(1) * stride_h;
  int out_width = input_shape.dim_size(2) * stride_w;
  auto input_sizes = Const<int>(scope, {batch_size, out_height, out_width, filter});

  // deconv
  // out_backprop, aka input.
  auto deconv1 = Conv2DTranspose(scope, input_sizes, filtersVar, input,
                                 {1, stride_h, stride_w, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  auto batchnorm_op = TFFusedBatchNorm(scope, {filter});
  auto batchnorm = batchnorm_op.Build(scope, deconv1, 0.001f, training);
  LOG(INFO) << "Node building status: " << scope.status();

  if(apply_dropout) {
    batchnorm = Dropout(scope, batchnorm, 0.5f);
    LOG(INFO) << "Node building status: " << scope.status();
  }

  auto relu = Relu(scope, batchnorm);
  LOG(INFO) << "Node building status: " << scope.status();

  return relu;
}

// Generator constructor to set variables and assigns
Generator::Generator(const ::tensorflow::Scope& scope) {
  this->w1 = TFVariable(scope.WithOpName("weight"), {NOISE_DIM, UNITS},
                        DT_FLOAT, true);
  LOG(INFO) << "Node building status: " << scope.status();

  auto rate = Const(scope, {0.01f});
  auto random_value = RandomNormal(scope, {NOISE_DIM, UNITS}, DT_FLOAT);
  TFAssign(scope, w1, Multiply(scope, random_value, rate));

  // filter, aka kernel
  this->filter =
      TFVariable(scope.WithOpName("filter"), {5, 5, 128, 256}, DT_FLOAT, true);
  auto random_value1 = GlorotUniform(scope, {5, 5, 128, 256});
  TFAssign(scope, filter, random_value1);

  // filter, aka kernel
  this->filter2 =
      TFVariable(scope.WithOpName("filter2"), {5, 5, 64, 128}, DT_FLOAT, true);
  auto random_value2 = GlorotUniform(scope, {5, 5, 64, 128});
  TFAssign(scope, filter2, random_value2);

  // filter, aka kernel
  this->filter3 = TFVariable(scope.WithOpName("filter3"),
                             {5, 5, NUM_CHANNELS, 64}, DT_FLOAT, true);
  auto random_value3 = GlorotUniform(scope, {5, 5, NUM_CHANNELS, 64});
  TFAssign(scope, filter3, random_value3);

  this->batchnorm_op = TFBatchNormalization(scope, {UNITS});
  this->batchnorm1_op = TFFusedBatchNorm(scope, {128});
  this->batchnorm2_op = TFFusedBatchNorm(scope, {64});
}

// Build model
Output Generator::Build(const ::tensorflow::Scope& scope, const int batch_size,
                        bool training, bool use_seed) {
  // random noise input
  Output noise;

  if (use_seed) {
    this->seed = Placeholder(scope, DT_FLOAT,
                             Placeholder::Shape({batch_size, NOISE_DIM}));
    noise = this->seed;
  } else {
    noise = RandomNormal(scope, {batch_size, NOISE_DIM}, DT_FLOAT);
  }
  LOG(INFO) << "Node building status: " << scope.status();

  // dense 1
  auto dense = MatMul(scope, noise, this->w1);
  LOG(INFO) << "Node building status: " << scope.status();

  // BatchNormalization
  auto variance_epsilon = Const<float>(scope, {0.001f});
  auto batchnorm =
      this->batchnorm_op.Build(scope, dense, {0}, variance_epsilon, training);
  LOG(INFO) << "Node building status: " << scope.status();

  // LeakyReLU
  auto leakyrelu =
      internal::LeakyRelu(scope, batchnorm, internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  // Reshape
  auto reshape1 = Reshape(scope, leakyrelu, {batch_size, 7, 7, 256});
  LOG(INFO) << "Node building status: " << scope.status();

  // Conv2DTranspose 1
  auto input_sizes = Const<int>(scope, {batch_size, 7, 7, 128});

  // out_backprop, aka input. here it's reshape1
  auto deconv1 = Conv2DTranspose(scope, input_sizes, this->filter, reshape1,
                                 {1, 1, 1, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  // BatchNormalization 1, use FusedBatchNorm
  auto batchnorm1 = this->batchnorm1_op.Build(scope, deconv1, 0.001f, training);
  LOG(INFO) << "Node building status: " << scope.status();

  // LeakyReLU 1
  auto leakyrelu1 =
      internal::LeakyRelu(scope, batchnorm1, internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  // Conv2DTranspose 2
  auto input_sizes2 = Const(scope, {batch_size, 14, 14, 64});

  auto deconv2 = Conv2DTranspose(scope, input_sizes2, this->filter2, leakyrelu1,
                                 {1, 2, 2, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  // BatchNormalization 2, use FusedBatchNorm
  auto batchnorm2 = this->batchnorm2_op.Build(scope, deconv2, 0.001f, training);
  LOG(INFO) << "Node building status: " << scope.status();

  // LeakyReLU 2
  auto leakyrelu2 =
      internal::LeakyRelu(scope, batchnorm2, internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  // Conv2DTranspose 3
  auto input_sizes3 = Const(scope, {batch_size, 28, 28, NUM_CHANNELS});
  auto deconv3 =
      Conv2DTranspose(scope.WithOpName("generator"), input_sizes3,
                      this->filter3, leakyrelu2, {1, 2, 2, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  auto output = Tanh(scope, deconv3);

  return output;
}

// Discriminator constructor to set variables and assigns
Discriminator::Discriminator(const ::tensorflow::Scope& scope) {
  this->conv1_weights = TFVariable(scope.WithOpName("conv1_weights"),
                                   {5, 5, NUM_CHANNELS, 64}, DT_FLOAT, true);
  auto random_value = GlorotUniform(scope, {5, 5, NUM_CHANNELS, 64});
  TFAssign(scope, this->conv1_weights, random_value);

  this->conv1_biases =
      TFVariable(scope.WithOpName("conv1_biases"), {64}, DT_FLOAT, true);
  TFAssign(scope, this->conv1_biases,
           Const<float>(scope, 0.0f, TensorShape({64})));

  this->conv2_weights = TFVariable(scope.WithOpName("conv2_weights"),
                                   {5, 5, 64, 128}, DT_FLOAT, true);
  auto random_value2 = GlorotUniform(scope, {5, 5, 64, 128});
  TFAssign(scope, this->conv2_weights, random_value2);

  this->conv2_biases =
      TFVariable(scope.WithOpName("conv2_biases"), {128}, DT_FLOAT, true);
  TFAssign(scope, this->conv2_biases,
           Const<float>(scope, 0.0f, TensorShape({128})));

  int s1 = IMAGE_SIZE;
  s1 = s1 / 4;
  s1 = std::pow(s1, 2) * 128;

  this->fc1_weights =
      TFVariable(scope.WithOpName("fc1_weights"), {s1, 1}, DT_FLOAT, true);
  auto random_value3 = GlorotUniform(scope, {s1, 1});
  TFAssign(scope, this->fc1_weights, random_value3);

  this->fc1_biases =
      TFVariable(scope.WithOpName("fc1_biases"), {1}, DT_FLOAT, true);
  TFAssign(scope, this->fc1_biases,
           Const<float>(scope, 0.0f, TensorShape({1})));
}

// Build model
Output Discriminator::Build(const ::tensorflow::Scope& scope,
                            const ::tensorflow::Input& inputs,
                            const int batch_size) {
  // Convnet Model begin
  auto conv2d_1 = Conv2D(scope, inputs, this->conv1_weights,
                         gtl::ArraySlice<int>{1, 2, 2, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  auto relu_1 =
      internal::LeakyRelu(scope, BiasAdd(scope, conv2d_1, this->conv1_biases),
                          internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  auto dropout_1 = Dropout(scope, relu_1, 0.3f);
  LOG(INFO) << "Node building status: " << scope.status();

  auto conv2d_2 = Conv2D(scope, dropout_1, this->conv2_weights,
                         gtl::ArraySlice<int>{1, 2, 2, 1}, "SAME");
  LOG(INFO) << "Node building status: " << scope.status();

  auto relu_2 =
      internal::LeakyRelu(scope, BiasAdd(scope, conv2d_2, this->conv2_biases),
                          internal::LeakyRelu::Alpha(0.3f));
  LOG(INFO) << "Node building status: " << scope.status();

  auto dropout_2 = Dropout(scope, relu_2, 0.3f);
  LOG(INFO) << "Node building status: " << scope.status();

  int s1 = IMAGE_SIZE;
  s1 = s1 / 4;
  s1 = std::pow(s1, 2) * 128;

  // reshape
  auto reshape1 = Reshape(scope, dropout_2, {batch_size, s1});
  LOG(INFO) << "Node building status: " << scope.status();

  // model output
  auto output =
      BiasAdd(scope.WithOpName("discriminator"),
              MatMul(scope, reshape1, this->fc1_weights), this->fc1_biases);
  // Convnet Model ends

  return output;
}

}  // namespace ops
}  // namespace tensorflow
