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

#ifndef TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_RL_TUNER_H_
#define TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_RL_TUNER_H_

#include <tuple>
#include <vector>

#include "tensorflow/cc/framework/ops.h"
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/framework/types.h"
#include "tensorflow/core/lib/gtl/array_slice.h"
#include "tensorflow/examples/cc/magenta/rl_tuner/note_rnn.h"

namespace tensorflow {

class RLTuner {
 public:
  RLTuner();
  ~RLTuner();

  void Train();

 private:
  const Scope& scope;
  ClientSession session;

  NoteRNN q_network;
  NoteRNN target_q_network;
  NoteRNN reward_rnn;

  Output reward_scores;
  Output action_scores;
  Output action_softmax;
  Output predicted_actions;
  Output next_action_scores;
  Output rewards;
  Output target_vals;
  Output future_rewards;
  Output action_mask;
  Output masked_action_scores;
  Output prediction_error;
  Output gradients;
  Output train_op;
  Output target_network_update;

  std::vector<Output> grad_outputs;

  Output apply_w;
  Output apply_b;
  Output apply_w_y;
  Output apply_b_y;

  Output update_target_w;
  Output update_target_b;
  Output update_target_w_y;
  Output update_target_b_y;

  Output temp_diff;
  Output lr;

  Output l2norm0;
  Output l2norm2;
  Output gradients0;
  Output gradients2;

  int discount_rate;
  int num_actions;
  int actions_executed_so_far;
  int num_steps;
  double exploration_p;
  int num_times_train_called;
  int num_times_store_called;
  int beat;
  int num_notes_in_melody;

  double note_rnn_reward_last_n;
  double music_theory_reward_last_n;

  Tensor last_observation;
  Tensor new_observation;

  Tensor x_tensor;

  std::vector<std::tuple<Tensor, Tensor, Tensor, Tensor, Tensor, Tensor, Tensor,
                         Tensor, Tensor, Tensor>>
      experience;

 private:
  Status Init();
  Status BuildGraph();

  std::tuple<Tensor, Tensor, Tensor> Action();
  void TrainingStep();
  Tensor GetRandomNote();
  Tensor PrimeInternalModels();
  Tensor PrimeInternalModel(const NoteRNN& q_network);
  double LinearAnnealing(int n, int total, double p_initial, double p_final);
  void Store(const Tensor& observation, const Tensor& state_h,
             const Tensor& state_c, const Tensor& action, const Tensor& reward,
             const Tensor& newobservation, const Tensor& newstate_h,
             const Tensor& newstate_c, const Tensor& new_reward_state_h,
             const Tensor& new_reward_state_c);

  void ResetComposition();
  void ResetXTensor();
  void UpdateXTensor();

  double Random();
  Output AssignSub(Output* target, const Output& source);

  // Reward
  double RewardFromRewardRnnScores(const Tensor& action,
                                   const Tensor& reward_scores);
  Tensor CollectReward(const Tensor& obs, const Tensor& action,
                       const Tensor& reward_scores);
  double RewardMusicTheory(const Tensor& action);
  double RewardKey(const Tensor& action);
};

}  // namespace tensorflow

#endif  // TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_RL_TUNER_H_
