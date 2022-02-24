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

//
// C++ implementation of pix2pix
// The correspoding python version:
// https://github.com/tensorflow/docs/blob/master/site/en/tutorials/generative/pix2pix.ipynb
//
// Author: Rock Zhuang
// Date  : May 01, 2020
//

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
// #include "tensorflow/cc/ops/function_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/cc/training/optimizer.h"
#include "tensorflow/core/framework/tensor.h"

#include "tensorflow/examples/cc/gan/pix2pix/const.h"
#include "tensorflow/examples/cc/gan/pix2pix/model.h"

#ifdef ENABLE_OPENCV
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#endif

#include "tensorflow/examples/cc/gan/pix2pix/test.h"

using namespace tensorflow;                 // NOLINT(build/namespaces)
using namespace tensorflow::ops;            // NOLINT(build/namespaces)
using namespace tensorflow::ops::internal;  // NOLINT(build/namespaces)
using namespace std;                        // NOLINT(build/namespaces)

int main() {
  Scope scope = Scope::NewRootScope();

#ifdef TESTING
  test(scope);

  return 0;
#endif

  // FunctionDefLibrary
  {
    auto arg = ops::_Arg(scope.WithOpName("arg"), DT_STRING, 0);
    Output stack = LoadImageTrain(scope, arg);
    auto retval1 = ops::_Retval(scope.WithOpName("retval"), stack, 0);

    tensorflow::GraphDef graph_def;
    TF_CHECK_OK(scope.ToGraphDef(&graph_def));

    //
    std::unique_ptr<Graph> graph(new Graph(OpRegistry::Global()));
    GraphConstructorOptions options;
    TF_CHECK_OK(ConvertGraphDefToGraph(options, graph_def, graph.get()));

    FunctionDef fdef_train;
    TF_CHECK_OK(GraphToFunctionDef(*graph, "LoadImageTrain", &fdef_train));
    FunctionDef fdef_test;
    TF_CHECK_OK(GraphToFunctionDef(*graph, "LoadImageTest", &fdef_test));
    LOG(INFO) << "Print: fdef_train: " << fdef_train.DebugString();
    LOG(INFO) << "Print: fdef_test: " << fdef_test.DebugString();

    //
    FunctionDefLibrary proto;
    *proto.add_function() = fdef_train;
    *proto.add_function() = fdef_test;
    Status status2 = scope.graph()->AddFunctionLibrary(proto);
    LOG(INFO) << "Print: status: " << status2;
  }

#ifdef VERBOSE
  {
    FunctionLibraryDefinition flib_def = scope.graph()->flib_def();

    std::vector<string> func_names = flib_def.ListFunctionNames();
    LOG(INFO) << "------------------func_names size: " << func_names.size();
    for (string str : func_names) {
      LOG(INFO) << "------------------func_name: " << str;
    }
  }
#endif

  // Dataset
  auto matching_files = MatchingFiles(scope, "/tmp/data/facades/train/*.jpg");

  // Prepare output_shapes
  vector<PartialTensorShape> output_shapes;
  output_shapes.emplace_back(tensorflow::PartialTensorShape({}));

  // TensorSliceDataset
  auto tensor_slice_dataset =
      TensorSliceDataset(scope, OutputList({matching_files}), output_shapes);

  vector<Tensor> outputs;
  ClientSession session(scope);

  // ParallelMapDataset
  NameAttrList load_image_train_fn;
  load_image_train_fn.set_name("LoadImageTrain");
  (*load_image_train_fn.mutable_attr())["T"].set_type(DT_FLOAT);
  auto train_dataset_map = ParallelMapDataset(
      scope, tensor_slice_dataset, OutputList(), AUTOTUNE, load_image_train_fn,
      {DT_FLOAT}, {{2, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS}});

  Status status = session.Run({}, {train_dataset_map}, {}, &outputs);
  LOG(INFO) << "Print: outputs 0 train_dataset_map: "
            << outputs[0].DebugString();

  // Shuffle and batch
  auto shuffle_dataset = ShuffleDataset(
      scope, train_dataset_map,
      Cast(scope, BUFFER_SIZE, DT_INT64),                  // buffer_size
      Cast(scope, 0, DT_INT64), Cast(scope, 0, DT_INT64),  // seedX
      std::initializer_list<DataType>{DT_FLOAT},           // output_types
      std::initializer_list<PartialTensorShape>{{}},       // output_shapes
      ShuffleDataset::ReshuffleEachIteration(true));
  auto batch_dataset = BatchDataset(
      scope, shuffle_dataset, Cast(scope, BATCH_SIZE, DT_INT64),  // batch_size
      std::initializer_list<DataType>{DT_FLOAT},       // output_types
      std::initializer_list<PartialTensorShape>{{}});  // output_shapes

  // Iterator
  Output iterator_output =
      Iterator(scope, "iterator1", "", vector<DataType>({DT_FLOAT}),
               vector<PartialTensorShape>({{}}));
  Operation make_iterator_op =
      MakeIterator(scope, batch_dataset, iterator_output);
  auto iterator_get_next =
      IteratorGetNext(scope, iterator_output, vector<DataType>({DT_FLOAT}),
                      vector<PartialTensorShape>({{}}));

#ifdef VERBOSE
  // Session
  // Note that ClientSession can extend graph before running, Session cannot.
  vector<Tensor> dataset_outputs;

  // Run make_iterator_output first
  TF_CHECK_OK(session.Run({}, {}, {make_iterator_op}, nullptr));
  while (session.Run({}, iterator_get_next.components, &dataset_outputs).ok()) {
    LOG(INFO) << "Print dataset_outputs: " << dataset_outputs[0].DebugString();
  }
#endif

  // TODO(Rock): Models
  
  return 0;
}
