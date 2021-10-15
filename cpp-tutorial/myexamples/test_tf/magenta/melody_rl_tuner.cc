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

//
// C++ implementation of Magenta rl_tuner module
// Using reinforcement learning with RNN(LSTM)
//
// Author: Rock Zhuang
// Date  : Jun 25, 2019
//

#include "tensorflow/examples/cc/magenta/rl_tuner/rl_tuner.h"

using tensorflow::RLTuner;

int main() {
  // RLTuner
  RLTuner rlTuner;
  rlTuner.Train();

  return 0;
}
