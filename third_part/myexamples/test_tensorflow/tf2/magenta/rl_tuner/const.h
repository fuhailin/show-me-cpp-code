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

#ifndef TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_CONST_H_
#define TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_CONST_H_

// #define VERBOSE 1
// #define TESTING 1

//
// Adjustable parameters
//

#define NUM_UNIT 128  // HIDDEN_SIZE
// #define MINIBATCH_SIZE 32
#define BATCH_SIZE 32  // BATCH_SIZE
#define TRAINING_STEPS 100000

//
// Don't change below
//

#define TIME_LEN 1  // NUM_STEPS, Here, it is always 1

// (DEFAULT_MAX_NOTE(84) - DEFAULT_MIN_NOTE(48) + NUM_SPECIAL_MELODY_EVENTS(2))
#define INPUT_SIZE 38

#endif  // TENSORFLOW_EXAMPLES_CC_MAGENTA_RL_TUNER_CONST_H_
