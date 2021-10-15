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
#ifndef TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_MODEL_H_
#define TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_MODEL_H_

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/ops/tf_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

class Generator {
 public:
  explicit Generator(const ::tensorflow::Scope& scope);

  Output Build(const ::tensorflow::Scope& scope, const int batch_size,
               bool training, bool use_seed = false);

  ::tensorflow::Output seed;

 private:
  ::tensorflow::Output w1;
  ::tensorflow::Output filter;
  ::tensorflow::Output filter2;
  ::tensorflow::Output filter3;

  TFBatchNormalization batchnorm_op;
  TFFusedBatchNorm batchnorm1_op;
  TFFusedBatchNorm batchnorm2_op;
};

class Discriminator {
 public:
  explicit Discriminator(const ::tensorflow::Scope& scope);

  Output Build(const ::tensorflow::Scope& scope,
               const ::tensorflow::Input& inputs, const int batch_size);

 private:
  ::tensorflow::Output conv1_weights;
  ::tensorflow::Output conv1_biases;
  ::tensorflow::Output conv2_weights;
  ::tensorflow::Output conv2_biases;
  ::tensorflow::Output fc1_weights;
  ::tensorflow::Output fc1_biases;
};

}  // namespace ops
}  // namespace tensorflow

#endif  // TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_MODEL_H_
