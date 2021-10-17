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
// #include "tensorflow/cc/training/optimizer.h"
#include "myexamples/test_tf/gan/dcgan/optimizer.h"

#include <algorithm>
#include <vector>

#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/standard_ops.h"
// #include "tensorflow/cc/ops/tf_ops.h"
#include "myexamples/test_tf/gan/dcgan/tf_ops.h"

#define LEARNING_RATE 0.0001f
#define BETA_1 0.9f
#define BETA_2 0.999f
#define EPSILON 1e-7

namespace tensorflow {
namespace ops {

AdamOptimizer::AdamOptimizer(const ::tensorflow::Scope& scope) {
    this->lr = Const<float>(scope, LEARNING_RATE);
    this->beta1 = Const<float>(scope, BETA_1);
    this->beta2 = Const<float>(scope, BETA_2);
    this->epsilon = Const<float>(scope, EPSILON);

    this->local_step = Variable(scope, {}, DT_FLOAT);
    TFAssign(scope, local_step, 1.0f);

    this->assign_add_local_step = AssignAdd(scope, local_step, 1.0f);

    this->beta1_power = Pow(scope, beta1, local_step);
    this->beta2_power = Pow(scope, beta2, local_step);
}

DataType DataTypeToBaseType(DataType data_type) {
    // convert ref datatype to base datatype
    int i_data_type = static_cast<int>(data_type);
    if (i_data_type > 100) {
        data_type = static_cast<DataType>(i_data_type - 100);
    }

    return data_type;
}

void AdamOptimizer::Build(const ::tensorflow::Scope& scope,
                          const std::vector<Output>& outputs,
                          const std::vector<Output>& trainable_variables) {
    // AddSymbolicGradients
    std::vector<Output> symb_grad_outputs;
    TF_CHECK_OK(AddSymbolicGradients(scope, outputs, trainable_variables,
                                     &symb_grad_outputs));
    LOG(INFO) << "Node building status: " << scope.status();

    // ApplyAdam trainable_variables
    int symb_grad_index = 0;
    for (auto var : trainable_variables) {
        // Variables m and v for ApplyAdam
        auto wm =
            Variable(scope, scope.GetTrainableVariableShape(var.node()->name()),
                     DataTypeToBaseType(var.type()));
        LOG(INFO) << "Node building status: " << scope.status();
        TFAssign(scope, wm, ZerosLike(scope, var));
        auto wv =
            Variable(scope, scope.GetTrainableVariableShape(var.node()->name()),
                     DataTypeToBaseType(var.type()));
        LOG(INFO) << "Node building status: " << scope.status();
        TFAssign(scope, wv, ZerosLike(scope, var));

        auto apply_adam =
            ApplyAdam(scope, var, wm, wv, beta1_power, beta2_power, lr, beta1,
                      beta2, epsilon, symb_grad_outputs[symb_grad_index++]);
        LOG(INFO) << "Node building status: " << scope.status();

        // Append it
        this->apply_adams.emplace_back(apply_adam);
    }

    // Append outputs to grad_outputs
    this->grad_outputs.reserve(this->grad_outputs.size() + outputs.size());
    this->grad_outputs.insert(this->grad_outputs.end(), outputs.begin(),
                              outputs.end());
}

// Build up optimizer
// For multi-gpus case, AddSymbolicGradients should be called outside,
//   so change symb_grad_outputs as a parameter
void AdamOptimizer::Build(const ::tensorflow::Scope& scope,
                          const std::vector<Output>& outputs,
                          const std::vector<Output>& trainable_variables,
                          const std::vector<Output>& symb_grad_outputs) {
    // ApplyAdam trainable_variables
    int symb_grad_index = 0;
    for (auto var : trainable_variables) {
        // Variables m and v for ApplyAdam
        auto wm =
            Variable(scope, scope.GetTrainableVariableShape(var.node()->name()),
                     DataTypeToBaseType(var.type()));
        LOG(INFO) << "Node building status: " << scope.status();
        TFAssign(scope, wm, ZerosLike(scope, var));
        auto wv =
            Variable(scope, scope.GetTrainableVariableShape(var.node()->name()),
                     DataTypeToBaseType(var.type()));
        LOG(INFO) << "Node building status: " << scope.status();
        TFAssign(scope, wv, ZerosLike(scope, var));

        auto apply_adam =
            ApplyAdam(scope, var, wm, wv, beta1_power, beta2_power, lr, beta1,
                      beta2, epsilon, symb_grad_outputs[symb_grad_index++]);
        LOG(INFO) << "Node building status: " << scope.status();

        // Append it
        this->apply_adams.emplace_back(apply_adam);
    }

    // Append outputs to grad_outputs
    this->grad_outputs.reserve(this->grad_outputs.size() + outputs.size());
    this->grad_outputs.insert(this->grad_outputs.end(), outputs.begin(),
                              outputs.end());
}

Status AdamOptimizer::Run(const ::tensorflow::Scope& scope,
                          const ::tensorflow::ClientSession& session,
                          std::vector<::tensorflow::Tensor>* outputs) {
    // Concat grad_outputs and apply_adam, and grad_outputs first
    std::vector<Output> fetch_outputs;
    fetch_outputs.reserve(this->grad_outputs.size() + this->apply_adams.size());
    fetch_outputs.insert(fetch_outputs.end(), this->grad_outputs.begin(),
                         this->grad_outputs.end());
    fetch_outputs.insert(fetch_outputs.end(), this->apply_adams.begin(),
                         this->apply_adams.end());

    // Run
    Status status = session.Run(fetch_outputs, outputs);
    if (status.ok()) {
        // Increase local_step
        std::vector<Tensor> assign_add_outputs;
        TF_CHECK_OK(
            session.Run({this->assign_add_local_step}, &assign_add_outputs));

#ifdef DEBUG
        // Print verbose message
        int step = static_cast<int>(assign_add_outputs[0].scalar<float>()());
        if (step % EVAL_FREQUENCY == 0) {
            LOG(INFO) << "Print step: " << step;
            for (int i = 0; i < this->grad_outputs.size(); i++) {
                LOG(INFO) << "Print grad_outputs " << i << ": "
                          << outputs->at(i).DebugString();
            }
        }
#endif
    }

    return status;
}

}  // namespace ops
}  // namespace tensorflow
