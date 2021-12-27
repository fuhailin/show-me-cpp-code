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
// Example for parsing tfrecord files in C++
// Author: Rock Zhuang
// Date  : Dec 12, 2018
//

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/common_runtime/device_factory.h"
#include "tensorflow/core/framework/dataset.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/kernels/data/iterator_ops.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/public/version.h"

#include "gflags/gflags.h"
 
DEFINE_string(filename, "/Users/vincent/Documents/projects/show-me-cpp-code/cpp-tutorial/myexamples/test_tf/data/test1.tfrecord", "filename");

// using namespace tensorflow;
// using namespace tensorflow::ops;

static tensorflow::Status TFRecordDataset(const tensorflow::Scope& scope,
                                          tensorflow::Input filenames,
                                          tensorflow::Input compression_type,
                                          tensorflow::Input buffer_size,
                                          tensorflow::Output& output) {
    if (!scope.ok()) return scope.status();

    // Prepare inputs
    auto _filenames = tensorflow::ops::AsNodeOut(scope, filenames);
    if (!scope.ok()) return scope.status();

    auto _compression_type = tensorflow::ops::AsNodeOut(scope, compression_type);
    if (!scope.ok()) return scope.status();

    auto _buffer_size = tensorflow::ops::AsNodeOut(scope, buffer_size);
    if (!scope.ok()) return scope.status();

    // Build node
    tensorflow::Node* ret;
    const auto unique_name = scope.GetUniqueNameForOp("TFRecordDataset");
    auto builder = tensorflow::NodeBuilder(unique_name, "TFRecordDataset")
                       .Input(_filenames)
                       .Input(_compression_type)
                       .Input(_buffer_size);

    // Update scope
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));

    if (!scope.ok()) return scope.status();

    scope.UpdateStatus(scope.DoShapeInference(ret));

    // Output
    output = tensorflow::Output(ret, 0);

    return tensorflow::Status::OK();
}

static tensorflow::Status Iterator(const tensorflow::Scope& scope,
                                   tensorflow::Output& output) {
    if (!scope.ok()) return scope.status();

    // Build node
    tensorflow::Node* ret;
    const auto unique_name = scope.GetUniqueNameForOp("Iterator");
    auto builder =
        tensorflow::NodeBuilder(unique_name, "Iterator")
            .Attr("shared_name", "iterator1")
            .Attr("container", "")
            .Attr("output_types",
                  std::vector<tensorflow::DataType>(
                      {tensorflow::DT_STRING}))  // TFRecordDataset only support
                                                 // DT_STRING, this doesn't make
                                                 // sense
            .Attr("output_shapes", std::vector<tensorflow::PartialTensorShape>(
                                       {{}}));  // TFRecordDataset only support
                                                // {}, this doesn't make sense

    // Update scope
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));

    if (!scope.ok()) return scope.status();

    scope.UpdateStatus(scope.DoShapeInference(ret));

    // Output
    output = tensorflow::Output(ret, 0);

    return tensorflow::Status::OK();
}

static tensorflow::Status MakeIterator(const tensorflow::Scope& scope,
                                       tensorflow::Input dataset,
                                       tensorflow::Input iterator,
                                       tensorflow::Output& output) {
    if (!scope.ok()) return scope.status();

    // Prepare inputs
    auto _dataset = tensorflow::ops::AsNodeOut(scope, dataset);
    if (!scope.ok()) return scope.status();

    auto _iterator = tensorflow::ops::AsNodeOut(scope, iterator);
    if (!scope.ok()) return scope.status();

    // Build node
    tensorflow::Node* ret;
    const auto unique_name = scope.GetUniqueNameForOp("MakeIterator");
    auto builder = tensorflow::NodeBuilder(unique_name, "MakeIterator")
                       .Input(_dataset)
                       .Input(_iterator);

    // Update scope
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));

    if (!scope.ok()) return scope.status();

    scope.UpdateStatus(scope.DoShapeInference(ret));

    // Output
    output = tensorflow::Output(ret, 0);

    return tensorflow::Status::OK();
}

static tensorflow::Status IteratorGetNext(const tensorflow::Scope& scope,
                                          tensorflow::Input iterator,
                                          tensorflow::Output& output) {
    if (!scope.ok()) return scope.status();

    // Prepare inputs
    auto _iterator = tensorflow::ops::AsNodeOut(scope, iterator);
    if (!scope.ok()) return scope.status();

    // // output_typs and output_shapes
    // const tensorflow::int64 pts[] = {38};
    // tensorflow::TensorShapeProto proto;
    // tensorflow::PartialTensorShape(pts).AsProto(&proto);

    // const tensorflow::int64 pts2[] = {0};
    // tensorflow::TensorShapeProto proto2;
    // tensorflow::PartialTensorShape(pts2).AsProto(&proto2);

    // std::vector<tensorflow::PartialTensorShape> output_shapes;
    // output_shapes.reserve(2);
    // output_shapes.push_back(proto);
    // output_shapes.push_back(proto2);

    // std::vector<tensorflow::DataType> output_types;
    // output_types.reserve(2);
    // output_types.push_back(tensorflow::DT_FLOAT);
    // output_types.push_back(tensorflow::DT_INT64);

    // Build node
    tensorflow::Node* ret;
    const auto unique_name = scope.GetUniqueNameForOp("IteratorGetNext");
    auto builder =
        tensorflow::NodeBuilder(unique_name, "IteratorGetNext")
            .Input(_iterator)
            .Attr("output_types",
                  std::vector<tensorflow::DataType>({tensorflow::DT_STRING}))  //
            .Attr("output_shapes",
                  std::vector<tensorflow::PartialTensorShape>({{}}));

    // Update scope
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));

    if (!scope.ok()) return scope.status();

    scope.UpdateStatus(scope.DoShapeInference(ret));

    // Output
    output = tensorflow::Output(ret, 0);

    return tensorflow::Status::OK();
}

// ParseExample start here, modified from example_parsing_ops_test.cc
enum BenchmarkType { kDense,
                     kSparse,
                     kVarLenDense };

static tensorflow::Tensor make_dense_default(tensorflow::DataType dtype,
                                             int feature_size) {
    return tensorflow::Tensor(dtype, tensorflow::TensorShape({feature_size}));
}

static tensorflow::Node* Constant(tensorflow::Graph* g,
                                  const tensorflow::Tensor& tensor) {
    tensorflow::Node* ret;
    TF_CHECK_OK(tensorflow::NodeBuilder(g->NewName("n"), "Const")
                    .Attr("dtype", tensor.dtype())
                    .Attr("value", tensor)
                    .Finalize(g, &ret));
    return ret;
}

static tensorflow::Status ParseExample(const tensorflow::Scope& scope,
                                       tensorflow::Tensor serialized,
                                       tensorflow::Output& output) {
    if (!scope.ok()) return scope.status();

    // For test only
    const int batch_size = 3;
    const BenchmarkType benchmark_type = kSparse;
    const int num_keys = 2;
    const int feature_size = 1;
    const tensorflow::DataType dtype = tensorflow::DT_INT64;

    // Prepare inputs
    tensorflow::Tensor names(tensorflow::DT_STRING,
                             tensorflow::TensorShape({batch_size}));

    std::vector<tensorflow::NodeBuilder::NodeOut> sparse_keys;
    std::vector<tensorflow::NodeBuilder::NodeOut> dense_keys;
    std::vector<tensorflow::NodeBuilder::NodeOut> dense_defaults;
    std::vector<tensorflow::DataType> sparse_types;
    std::vector<tensorflow::PartialTensorShape> dense_shapes;

    for (int i = 0; i < num_keys; ++i) {
        tensorflow::Tensor key(tensorflow::DT_STRING, tensorflow::TensorShape());
        key.scalar<tensorflow::tstring>()() = tensorflow::strings::Printf("feature_%d", i);
        switch (benchmark_type) {
            case kDense:
                dense_keys.emplace_back(Constant(scope.graph(), key));
                dense_defaults.emplace_back(
                    Constant(scope.graph(), make_dense_default(dtype, feature_size)));
                dense_shapes.push_back(tensorflow::PartialTensorShape({feature_size}));
                break;
            case kVarLenDense:
                dense_keys.emplace_back(Constant(scope.graph(), key));
                dense_defaults.emplace_back(
                    Constant(scope.graph(), make_dense_default(dtype, 1)));
                dense_shapes.push_back(tensorflow::PartialTensorShape({-1}));
                break;
            case kSparse:
                sparse_keys.emplace_back(Constant(scope.graph(), key));

                // For test only
                if (i == 0)
                    sparse_types.push_back(tensorflow::DT_INT64);
                else
                    sparse_types.push_back(tensorflow::DT_STRING);
                break;
        }
    }

    // Build node
    tensorflow::Node* ret;
    const auto unique_name = scope.GetUniqueNameForOp("ParseExample");
    auto builder = tensorflow::NodeBuilder(unique_name, "ParseExample")
                       .Input(Constant(scope.graph(), serialized))
                       .Input(Constant(scope.graph(), names))
                       .Input(sparse_keys)
                       .Input(dense_keys)
                       .Input(dense_defaults)
                       .Attr("sparse_types", sparse_types)
                       .Attr("dense_shapes", dense_shapes);

    // Update scope
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(scope.graph(), &ret));

    if (!scope.ok()) return scope.status();

    scope.UpdateStatus(scope.DoShapeInference(ret));

    // Output
    output = tensorflow::Output(ret, 0);

    return tensorflow::Status::OK();
}

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    tensorflow::Scope root = tensorflow::Scope::NewRootScope();

    // TFRecordDataset Node
    std::cout << "test: " << FLAGS_filename << std::endl;
    tensorflow::Tensor filenames(FLAGS_filename);  // Check tfrecord_test.py which generates the
                                 // tfrecord file
    tensorflow::Tensor compression_type("ZLIB");
    tensorflow::Tensor buffer_size((tensorflow::int64)1024);

    tensorflow::Output dataset_output;
    if (!TFRecordDataset(root, filenames, compression_type, buffer_size,
                         dataset_output)
             .ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << root.status();

        return root.status().code();
    }

    // Iterator Node
    tensorflow::Output iterator_output;
    if (!Iterator(root, iterator_output).ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << root.status();

        return root.status().code();
    }

    // MakeIterator Node
    tensorflow::Output make_iterator_output;
    if (!MakeIterator(root, dataset_output, iterator_output, make_iterator_output)
             .ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << root.status();

        return root.status().code();
    }

    // IteratorGetNext Node
    tensorflow::Output iterator_get_next_output;
    if (!IteratorGetNext(root, iterator_output, iterator_get_next_output).ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << root.status();

        return root.status().code();
    }

    std::vector<tensorflow::Tensor> outputs;
    tensorflow::ClientSession session(root);

    // Run make_iterator_output first, then iterator_get_next_output
    TF_CHECK_OK(session.Run({}, {}, {make_iterator_output.op()}, &outputs));
    TF_CHECK_OK(session.Run(
        {}, {dataset_output, iterator_output, iterator_get_next_output},
        {iterator_get_next_output.op()}, &outputs));

    LOG(INFO) << "Print: " << outputs[0].shape() << ", " << outputs[1].shape()
              << ", " << outputs[2].shape();
    LOG(INFO) << "Print: " << outputs[0].DebugString() << ", "
              << outputs[1].DebugString() << ", " << outputs[2].DebugString();

    auto result = outputs[2].template scalar<tensorflow::tstring>()();
    LOG(INFO) << "Print: result: " << result;

    // Input for ParseExample
    int record_index = 0;
    tensorflow::Tensor record_string(tensorflow::DT_STRING,
                                     tensorflow::TensorShape({3}));
    record_string.template vec<tensorflow::tstring>()(record_index++) = result;

    // Iterator get_next
    while (session.Run({iterator_get_next_output}, &outputs).ok()) {
        result = outputs[0].template scalar<tensorflow::tstring>()();
        record_string.template vec<tensorflow::tstring>()(record_index++) = result;

        LOG(INFO) << "Print: result: " << result;
    }

    // ParseExample, which supports batch input
    tensorflow::Output parse_example_output;
    if (!ParseExample(root, record_string, parse_example_output).ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << root.status();

        return root.status().code();
    }

    // Run parse_example_output
    // Fours outputs from one node
    TF_CHECK_OK(session.Run({},
                            {tensorflow::Output(parse_example_output.node(), 0),
                             tensorflow::Output(parse_example_output.node(), 1),
                             tensorflow::Output(parse_example_output.node(), 2),
                             tensorflow::Output(parse_example_output.node(), 3)},
                            {parse_example_output.op()}, &outputs));

    LOG(INFO) << "Print: " << outputs[0].shape() << ", " << outputs[1].shape()
              << ", " << outputs[2].shape() << ", " << outputs[3].shape();
    LOG(INFO) << "Print: " << outputs[0].DebugString() << outputs[1].DebugString()
              << outputs[2].DebugString() << outputs[3].DebugString();

    return 0;
}
