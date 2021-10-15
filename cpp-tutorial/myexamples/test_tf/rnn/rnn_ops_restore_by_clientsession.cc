/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

//
// Example for using rnn ops in C++, Vanilla RNN for now
// Load graph from a frozen model file by ClientSession
//
// Author: Rock Zhuang
// Date  : June 04, 2019
//

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/str_util.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

#define HIDDEN_SIZE 16
#define SEQ_LENGTH 10
#define VOCAB_SIZE 8  // "helo wrd"
#define TEST_SEQ_LENGTH 1
#define GENERATE_STEPS 100

// #define VERBOSE 1
// #define TESTING 1

int main(int argc, char* argv[]) {
  // Frozen graph file which is saved in rnn_ops_test
  string graph_path = "/tmp/vanilla_rnn_frozen.pb";

  string input_layer = "x_eval";
  string label_layer = "y_eval";
  string h_prev_layer = "h_prev";
  string output_layer1 = "vanilla_rnn_output_eval:0";
  string output_layer2 = "vanilla_rnn_output_eval:1";

  // We need to call this to set up global state for TensorFlow.
  port::InitMain(argv[0], &argc, &argv);

  // vocabulary vs index
  const map<int, char> index_vocab_dic = {{0, ' '}, {1, 'e'}, {2, 'd'},
                                          {3, 'h'}, {4, 'l'}, {5, 'o'},
                                          {6, 'r'}, {7, 'w'}};
  map<char, int> vocab_index_dic;
  for (auto iter = index_vocab_dic.begin(); iter != index_vocab_dic.end();
       iter++) {
    // LOG(INFO) << "----------------index_vocab_dic: " << iter->first <<' ' <<
    // iter->second;

    vocab_index_dic.insert(pair<char, int>(iter->second, iter->first));
  }

  auto root = Scope::NewRootScope();
  ClientSession clientSession(root);

  // First we load and initialize the model.
  Status load_graph_status = clientSession.RestoreModel(graph_path);
  if (!load_graph_status.ok()) {
    LOG(ERROR) << load_graph_status;
    return -1;
  }

  // Inputs
  Tensor x_tensor(DT_FLOAT, TensorShape({TEST_SEQ_LENGTH, VOCAB_SIZE, 1}));
  auto e_2d = x_tensor.shaped<float, 2>({TEST_SEQ_LENGTH, VOCAB_SIZE * 1});
  char test_char = ' ';  // randomly

  LOG(INFO) << __FUNCTION__
            << "----------------Evaluate test_char: " << test_char;

  // Prepare y
  Tensor y_tensor(DT_FLOAT, TensorShape({TEST_SEQ_LENGTH}));
  // y value make no sense in the evaluation process
  y_tensor.vec<float>()(0) = 0;

  // Prepare hidden tensor
  Tensor h_prev_tensor(DT_FLOAT, TensorShape({HIDDEN_SIZE, 1}));
  typename TTypes<float>::Matrix h_prev_t = h_prev_tensor.matrix<float>();
  h_prev_t.setZero();

  for (int i = 0; i < GENERATE_STEPS; i++) {
    // one-hot processing
    {
      // Assign a 1 x VOCAB_SIZE * 1 matrix (really vector) to a slice of size
      Eigen::Tensor<float, 2, Eigen::RowMajor> m(1, VOCAB_SIZE * 1);
      m.setZero();

      // one-hot processing for one character
      auto search = vocab_index_dic.find(test_char);
      int vocab_index = search->second;
      m(0, vocab_index) = 1.0f;

      // set e_2d

      // should be (0, 0) all the time
      Eigen::DSizes<Eigen::DenseIndex, 2> indices(0, 0);
      Eigen::DSizes<Eigen::DenseIndex, 2> sizes(1, VOCAB_SIZE * 1);
      e_2d.slice(indices, sizes) = m;
    }

    vector<Tensor> outputs;
    vector<Tensor> outputs_topk;

    // Run vanilla_rnn_output_eval
    Status run_status =
        clientSession.Run(RunOptions(),
                          {{input_layer, x_tensor},
                           {label_layer, y_tensor},
                           {h_prev_layer, h_prev_tensor}},
                          {output_layer1, output_layer2}, {}, &outputs);
    if (!run_status.ok()) {
      LOG(ERROR) << "Running model failed: " << run_status;
      return -1;
    }

#ifdef VERBOSE
    // output[0] => p, outputs[1] => h
    LOG(INFO) << "Print vanilla_rnn_output_eval: " << outputs[0].DebugString()
              << ", " << outputs[1].DebugString();
#endif

    // top 1
    Tensor topk_input_tensor(DT_FLOAT, TensorShape({VOCAB_SIZE}));
    topk_input_tensor.flat<float>() = outputs[0].flat<float>();

    // Run topk from loaded graph
    string topk_input_layer = "topk_input";
    string topk_output_layer1 = "topk:0";
    string topk_output_layer2 = "topk:1";
    run_status = clientSession.Run(
        RunOptions(), {{topk_input_layer, topk_input_tensor}},
        {topk_output_layer1, topk_output_layer2}, {}, &outputs_topk);
    if (!run_status.ok()) {
      LOG(ERROR) << "Running model failed: " << run_status;
      return -1;
    }

#ifdef VERBOSE
    // outputs_topk[0] => topk.values, outputs_topk[1] => topk.indices
    LOG(INFO) << "Print topk: " << outputs_topk[0].DebugString() << ", "
              << outputs_topk[1].DebugString();
#endif

    // update test_char for x_tensor
    int index = outputs_topk[1].scalar<int>()();
    auto search = index_vocab_dic.find(index);
    test_char = search->second;
    // #ifdef VERBOSE
    LOG(INFO) << __FUNCTION__
              << "----------------Evaluate test_char: " << test_char;
    // #endif

    // update h_prev_tensor
    CHECK(h_prev_tensor.CopyFrom(
        outputs[1].Slice(0, 1),
        {outputs[1].dim_size(1), outputs[1].dim_size(2)}));
  }

  return 0;
}
