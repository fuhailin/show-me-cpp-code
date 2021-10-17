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
#ifndef TENSORFLOW_CC_TRAINING_OPTIMIZER_H_
#define TENSORFLOW_CC_TRAINING_OPTIMIZER_H_

#include <vector>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"

namespace tensorflow {
namespace ops {

class AdamOptimizer {
   public:
    explicit AdamOptimizer(const ::tensorflow::Scope& scope);

    void Build(const ::tensorflow::Scope& scope,
               const std::vector<Output>& outputs,
               const std::vector<Output>& trainable_variables);
    void Build(const ::tensorflow::Scope& scope,
               const std::vector<Output>& outputs,
               const std::vector<Output>& trainable_variables,
               const std::vector<Output>& symb_grad_outputs);

    Status Run(const ::tensorflow::Scope& scope,
               const ::tensorflow::ClientSession& session,
               std::vector<Tensor>* outputs);

   private:
    // Store all ApplyAdam outputs
    std::vector<Output> apply_adams;

    // Store grad outputs from AddSymbolicGradients
    std::vector<Output> grad_outputs;

    // learning rate
    Output lr;

    // beta*
    Output beta1;
    Output beta2;
    Output beta1_power;
    Output beta2_power;

    Output epsilon;

    // steps
    Output local_step;
    Output assign_add_local_step;
};

}  // namespace ops
}  // namespace tensorflow

#endif  // TENSORFLOW_CC_TRAINING_OPTIMIZER_H_
