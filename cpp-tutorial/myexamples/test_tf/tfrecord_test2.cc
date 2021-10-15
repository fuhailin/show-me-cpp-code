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
// Example for parsing tfrecord files in C++ using ops wrapper
// Author: Rock Zhuang
// Date  : Dec 26, 2018
//

#include <iostream>

#include "gflags/gflags.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/kernels/data/iterator_ops.h"

DEFINE_string(filename, "/Users/vincent/Documents/projects/show-me-cpp-code/cpp-tutorial/myexamples/test_tf/data/test1.tfrecord", "filename");

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace tensorflow::ops::internal;
using namespace std;

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "test: " << FLAGS_filename << std::endl;
    Scope root = Scope::NewRootScope();

    // TFRecordDataset Node
    Tensor filenames(FLAGS_filename);  // Check tfrecord_test.py which
                                       // generates the tfrecord file
    Tensor compression_type("ZLIB");
    Tensor buffer_size((int64)1024);

    Output dataset_output =
        TFRecordDataset(root, filenames, compression_type, buffer_size);
    Output iterator_output =
        Iterator(root, "iterator1", "",
                 vector<tensorflow::DataType>({tensorflow::DT_STRING}),
                 vector<tensorflow::PartialTensorShape>({{}}));
    Operation make_iterator_op =
        MakeIterator(root, dataset_output, iterator_output);
    auto iterator_get_next =
        IteratorGetNext(root, iterator_output,
                        vector<tensorflow::DataType>({tensorflow::DT_STRING}),
                        vector<tensorflow::PartialTensorShape>({{}}));

    vector<Tensor> outputs;
    ClientSession session(root);

    // Run make_iterator_output first, then iterator_get_next_output
    TF_CHECK_OK(session.Run({}, {}, {make_iterator_op}, nullptr));
    TF_CHECK_OK(
        session.Run({}, {dataset_output, iterator_output, iterator_get_next[0]},
                    {iterator_get_next.operation}, &outputs));

    // LOG(INFO) << "Print: " << outputs[0].DebugString() << ", " <<
    // outputs[1].DebugString() << ", " << outputs[2].DebugString();

    auto result = outputs[2].template scalar<tstring>()();
    LOG(INFO) << "Print: result: " << result;

    // Input for ParseExample
    int record_index = 0;
    tensorflow::Tensor record_string(tensorflow::DT_STRING,
                                     tensorflow::TensorShape({3}));
    record_string.template vec<tstring>()(record_index++) = result;

    // Iterator get_next
    while (session
               .Run({}, {iterator_get_next[0]}, {iterator_get_next.operation},
                    &outputs)
               .ok()) {
        result = outputs[0].template scalar<tstring>()();
        record_string.template vec<tstring>()(record_index++) = result;

        LOG(INFO) << "Print: result: " << result;
    }

    // ParseExample, which supports batch input
    const int batch_size = 3;

    // Prepare inputs
    Tensor names(DT_STRING, TensorShape({batch_size}));

    vector<Output> sparse_keys;
    vector<Output> dense_keys;
    vector<Output> dense_defaults;
    vector<DataType> sparse_types;
    vector<PartialTensorShape> dense_shapes;

    sparse_keys.push_back(Const<tstring>(root, "feature_0", TensorShape({})));
    sparse_keys.push_back(Const<tstring>(root, "feature_1", TensorShape({})));

    sparse_types.push_back(DT_INT64);
    sparse_types.push_back(DT_STRING);

    auto parse_example = ParseExample(
        root, record_string, names, InputList(sparse_keys), InputList(dense_keys),
        InputList(dense_defaults), sparse_types, dense_shapes);

    // Run parse_example_output
    TF_CHECK_OK(session.Run(parse_example.sparse_values, &outputs));
    LOG(INFO) << "Print parse_example: " << outputs[0].DebugString() << ", "
              << outputs[1].DebugString();

    return 0;
}