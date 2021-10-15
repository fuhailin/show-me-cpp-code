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
#ifndef TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_FUNCTION_H_
#define TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_FUNCTION_H_

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/ops/tf_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

Output DiscriminatorLoss(const Scope& scope, const Input& real_output,
                         const Input& fake_output);
Output GeneratorLoss(const Scope& scope, const Input& fake_output);

std::tuple<Output, Output> LoadP2P(const Scope& scope,
                                   const Output& image_file);
std::tuple<Output, Output> ResizeP2P(const Scope& scope,
                                     const Output& input_image,
                                     const Output& real_image, const int height,
                                     const int width);
std::tuple<Output, Output> RandomCropP2P(const Scope& scope,
                                         const Output& input_image,
                                         const Output& real_image);
std::tuple<Output, Output> NormalizeP2P(const Scope& scope,
                                        const Output& input_image,
                                        const Output& real_image);
std::tuple<Output, Output> RandomJitterP2P(const Scope& scope,
                                           const Output& input_image,
                                           const Output& real_image);
std::tuple<Output, Output> LoadImageTrainX(const Scope& scope,
                                           const Output& image_file);
std::tuple<Output, Output> LoadImageTestX(const Scope& scope,
                                          const Output& image_file);
Output LoadImageTrain(const Scope& scope, const Output& image_file);
Output LoadImageTest(const Scope& scope, const Output& image_file);

}  // namespace ops
}  // namespace tensorflow

#endif  // TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_FUNCTION_H_
