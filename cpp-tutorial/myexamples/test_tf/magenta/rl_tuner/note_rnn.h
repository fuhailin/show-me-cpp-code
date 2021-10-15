/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_NOTE_RNN_H_
#define TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_NOTE_RNN_H_

#include <memory>
#include <string>
#include <vector>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/rnn_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/cc/training/queue_runner.h"
#include "tensorflow/core/protobuf/queue_runner.pb.h"

using tensorflow::ops::RNNSoftmaxLoss;
using tensorflow::ops::internal::BlockLSTM;

namespace tensorflow {

class NoteRNN {
 public:
  explicit NoteRNN(const Scope& s, const ClientSession& ses);
  ~NoteRNN();

  Status Restore(const string& file_path);

  Status UpdateState(const Tensor& h, const Tensor& c);

  operator ::tensorflow::Output() const { return logits; }
  operator ::tensorflow::Input() const { return logits; }

 private:
  friend class RLTuner;

  // Trainable variables
  Output w;
  Output b;
  Output w_y;
  Output b_y;
  Output cs;
  Output ada_w;
  Output ada_b;
  Output ada_w_y;
  Output ada_b_y;

  // Inputs
  Output x;
  Output y;
  Output cs_prev;
  Output h_prev;

  Tensor y_tensor;
  Tensor h_prev_tensor;
  Tensor cs_prev_tensor;

  std::shared_ptr<BlockLSTM> block_lstm;

 private:
  const Scope& scope;
  const ClientSession& session;

  std::shared_ptr<RNNSoftmaxLoss> rnn_softmax_loss;

  std::vector<Output> grad_outputs;

  Output logits;

  // Placeholders for assigning variables
  Output w_ph;
  Output b_ph;
  Output w_y_ph;
  Output b_y_ph;
  Output ada_w_ph;
  Output ada_b_ph;
  Output ada_w_y_ph;
  Output ada_b_y_ph;

  // Initial values for assigning variables
  Output rate;
  Output random_value;
  Output random_value2;
  Output zero_like;
  Output zero_like2;
  Output zero_like3;
  Output zero_like4;
  Output zero_like5;
  Output zero_like6;

  Output assign_w;
  Output assign_b;
  Output assign_w_y;
  Output assign_b_y;
  Output assign_ada_w;
  Output assign_ada_b;
  Output assign_ada_w_y;
  Output assign_ada_b_y;

 private:
  Status BuildGraph();
};

}  // namespace tensorflow

#endif  // TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_NOTE_RNN_H_
