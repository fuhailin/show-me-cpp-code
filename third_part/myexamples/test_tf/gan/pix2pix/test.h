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

#ifndef TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_TEST_H_
#define TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_TEST_H_

#include <string>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/substitute.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/common_runtime/device.h"
#include "tensorflow/core/common_runtime/device_mgr.h"
#include "tensorflow/core/common_runtime/device_set.h"
#include "tensorflow/core/common_runtime/function.h"
#include "tensorflow/core/common_runtime/lower_case_op.h"
#include "tensorflow/core/common_runtime/lower_functional_ops.h"
#include "tensorflow/core/common_runtime/lower_if_op.h"
#include "tensorflow/core/common_runtime/lower_while_op.h"
#include "tensorflow/core/common_runtime/placer.h"
#include "tensorflow/core/framework/attr_value_util.h"
#include "tensorflow/core/framework/function.h"
#include "tensorflow/core/framework/function.pb.h"
#include "tensorflow/core/framework/graph_def_util.h"
#include "tensorflow/core/framework/graph_to_functiondef.h"
#include "tensorflow/core/framework/node_def.pb.h"
#include "tensorflow/core/framework/node_def_util.h"
#include "tensorflow/core/framework/op_def.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/versions.pb.h"
#include "tensorflow/core/graph/algorithm.h"
#include "tensorflow/core/graph/control_flow.h"
#include "tensorflow/core/graph/graph_node_util.h"
#include "tensorflow/core/graph/tensor_id.h"
#include "tensorflow/core/grappler/graph_view.h"
#include "tensorflow/core/grappler/grappler_item.h"
#include "tensorflow/core/grappler/op_types.h"
#include "tensorflow/core/grappler/utils.h"
#include "tensorflow/core/grappler/utils/functions.h"
#include "tensorflow/core/lib/gtl/map_util.h"
#include "tensorflow/examples/cc/gan/pix2pix/const.h"
#include "tensorflow/examples/cc/gan/pix2pix/function.h"

#define MOMENTUM 0.99f

using namespace tensorflow;                 // NOLINT(build/namespaces)
using namespace tensorflow::ops;            // NOLINT(build/namespaces)
using namespace tensorflow::ops::internal;  // NOLINT(build/namespaces)
using namespace std;                        // NOLINT(build/namespaces)

std::string DetailedDebugString(const Tensor& tensor) {
    return strings::StrCat("Tensor<type: ", DataTypeString(tensor.dtype()),
                           " shape: ", tensor.shape().DebugString(),
                           " values: ", tensor.SummarizeValue(-1, true), ">");
}

#ifdef TESTING
template <typename T>
Tensor AsScalar(const T& val) {
    Tensor ret(DataTypeToEnum<T>::value, {});
    ret.scalar<T>()() = val;
    return ret;
}

FunctionDef INIT() {
    return FunctionDefHelper::Define(
        // Name
        "INIT",
        // Args
        {"x: T"},
        // Return values
        {"y: T"},
        // Attr def
        {"T: {float, double, int32, int64}"},
        // Nodes
        {
            {{"y"}, "Identity", {"x"}, {{"T", "$T"}}},
        });
}

FunctionDef NEXT() {
    // const Tensor kTwo = AsScalar<int64>(2);
    return FunctionDefHelper::Define(
        // Name
        "NEXT",
        // Args
        {"a: T", "b: T"},
        // Return values
        {"c: T"},
        // Attr def
        {"T: {float, double, int32, int64}"},
        // Nodes
        {
            {{"c"}, "Mul", {"a", "b"}, {{"T", "$T"}}},
        });
}

FunctionDef FINALIZE() {
    return FunctionDefHelper::Define(
        // Name
        "FINALIZE",
        // Args
        {"i: T"},
        // Return values
        {"o: T"},
        // Attr def
        {"T: {float, double, int32, int64}"},
        // Nodes
        {
            {{"o"}, "Identity", {"i"}, {{"T", "$T"}}},
        });
}

void test(const Scope& scope) {
    {
        Scope scope_l = Scope::NewRootScope();

        auto logits = Const(scope_l, {{-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}});
        auto ones_like = OnesLike(scope_l, logits);
        auto scel = SigmoidCrossEntropyWithLogits(scope_l, ones_like, logits);
        auto result = ReduceMean(scope_l, scel, {0, 1});

        tensorflow::GraphDef graph_def;
        TF_CHECK_OK(scope_l.ToGraphDef(&graph_def));

        // Write raw graph
        const std::string filename =
            tensorflow::strings::StrCat("/tmp/", "graph_raw.pb");
        TF_CHECK_OK(tensorflow::WriteTextProto(tensorflow::Env::Default(), filename,
                                               graph_def));

        //
        std::unique_ptr<Graph> graph(new Graph(OpRegistry::Global()));
        GraphConstructorOptions options;
        TF_CHECK_OK(ConvertGraphDefToGraph(options, graph_def, graph.get()));

        FunctionDef fdef;
        TF_CHECK_OK(GraphToFunctionDef(*graph, "test_fn", &fdef));

        LOG(INFO) << "Print: fdef: " << fdef.DebugString();

        //
        FunctionDefLibrary proto;
        *proto.add_function() = INIT();
        *proto.add_function() = NEXT();
        *proto.add_function() = FINALIZE();
        *proto.add_function() = fdef;

        Status status2 = scope_l.graph()->AddFunctionLibrary(proto);
        LOG(INFO) << "Print: status: " << status2;

        vector<Tensor> outputs;
        ClientSession session(scope_l);

        Status status = session.Run({}, {result}, {}, &outputs);

        FunctionLibraryDefinition flib_def = scope_l.graph()->flib_def();

        std::vector<string> func_names = flib_def.ListFunctionNames();
        LOG(INFO) << "------------------func_names size: " << func_names.size();
        for (string str : func_names) {
            LOG(INFO) << "------------------func_name: " << str;
        }

#if 0
    FunctionLibraryDefinition flib_def =
      FunctionLibraryDefinition(OpRegistry::Global(), graph_def.library());
    std::unique_ptr<Graph> graph = absl::make_unique<Graph>(flib_def);

    LOG(INFO) << "------------------graph->num_node_ids(): " << graph->num_node_ids();

    for (int i = 0; i < graph->num_node_ids(); ++i) {
      Node* n = graph->FindNodeId(i);
      // if (n == nullptr) continue;  // deleted node
      LOG(INFO) << "------------------graph node: " << n->name();
    }

    Node* n = result.node();

    // Native function call can also produce dead tensors if the function body
    // has mergeless switches.
    const FunctionDef* fdef = flib_def.Find(n->type_string());
    if (fdef != nullptr) {
      std::unique_ptr<FunctionBody> nested_fbody;

      NameAttrList func;
      TF_CHECK_OK(NameAndAttrsFromFunctionCall(n->def(), &func));
      TF_CHECK_OK(FunctionDefToBodyHelper(*fdef, AttrSlice(&func.attr()),
                                                 &flib_def, &nested_fbody));

      LOG(INFO) << "------------------Function call: " << func.name()
                << " node=" << n->name();
        
    } else {
      LOG(INFO) << "------------------fdef == nullptr ";
    }
#endif
    }

    {
        // t = tf.constant([[[1, 1, 1], [2, 2, 2]],
        //                [[3, 3, 3], [4, 4, 4]],
        //                [[5, 5, 5], [6, 6, 6]]])
        // tf.strided_slice(t, [1, 0, 0], [2, 1, 3], [1, 1, 1])  # [[[3, 3, 3]]]
        // tf.strided_slice(t, [1, 0, 0], [2, 2, 3], [1, 1, 1])  # [[[3, 3, 3],
        //                                                       #   [4, 4, 4]]]
        // tf.strided_slice(t, [1, -1, 0], [2, -3, 3], [1, -1, 1])  # [[[4, 4, 4],
        //                                                          #   [3, 3, 3]]]

        auto t = Const(scope, {{{1, 1, 1}, {2, 2, 2}},
                               {{3, 3, 3}, {4, 4, 4}},
                               {{5, 5, 5}, {6, 6, 6}}});
        auto ss_1 = StridedSlice(scope, t, {1, 0, 0}, {2, 1, 3}, {1, 1, 1});
        auto ss_2 = StridedSlice(scope, t, {1, 0, 0}, {2, 2, 3}, {1, 1, 1});
        auto ss_3 = StridedSlice(scope, t, {1, -1, 0}, {2, -3, 3}, {1, -1, 1});

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status = session.Run({}, {ss_1, ss_2, ss_3}, {}, &outputs);

        LOG(INFO) << "Print: outputs 0: " << DetailedDebugString(outputs[0]);
        LOG(INFO) << "Print: outputs 1: " << DetailedDebugString(outputs[1]);
        LOG(INFO) << "Print: outputs 2: " << DetailedDebugString(outputs[2]);
    }

    {
        auto t = Const(scope, {256});
        // auto c = Concat(scope, {{0}, {256}, {0}}, {0});
        auto c = Stack(scope, {Const(scope, {0}), t, Const(scope, {0})});
        LOG(INFO) << "---------------------Node building status: "
                  << scope.status();

        auto pos = Reshape(scope, c, {3});
        LOG(INFO) << "---------------------Node building status: "
                  << scope.status();

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status = session.Run({}, {pos, c}, {}, &outputs);

        LOG(INFO) << "Print: concat outputs 0: " << DetailedDebugString(outputs[0]);
    }

    {
        auto read_file =
            ReadFile(scope, "/home/rock/ml/data/facades/train/100.jpg");
        auto image = DecodeJpeg(scope, read_file);
        auto shape = Shape(scope, image);
        Output w = StridedSlice(scope, shape, {1}, {2}, {1});
        Output w1 = Div(scope, w, 2);
        LOG(INFO) << "Node building status: " << scope.status();

        auto stack =
            Stack(scope, {Const(scope, {IMAGE_SIZE}), w1, Const(scope, {3})});
        auto pos = Reshape(scope, stack, {3});
        LOG(INFO) << "Node building status: " << scope.status();

        auto stack2 = Stack(scope, {Const(scope, {0}), w1, Const(scope, {0})});
        auto pos2 = Reshape(scope, stack2, {3});
        LOG(INFO) << "Node building status: " << scope.status();

        auto stack3 =
            Stack(scope, {Const(scope, {IMAGE_SIZE}), w, Const(scope, {3})});
        auto pos3 = Reshape(scope, stack3, {3});
        LOG(INFO) << "Node building status: " << scope.status();

        auto real_image = Cast(
            scope, StridedSlice(scope, image, {0, 0, 0}, pos, {1, 1, 1}), DT_FLOAT);
        LOG(INFO) << "Node building status: " << scope.status();

        auto input_image = Cast(
            scope, StridedSlice(scope, image, pos2, pos3, {1, 1, 1}), DT_FLOAT);
        LOG(INFO) << "Node building status: " << scope.status();

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status =
            session.Run({}, {input_image, real_image, w, pos, image}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
        LOG(INFO) << "Print: outputs 1: " << outputs[1].DebugString();
        LOG(INFO) << "Print: outputs 2: " << outputs[2].DebugString();
        LOG(INFO) << "Print: outputs 3: " << outputs[3].DebugString();
        // LOG(INFO) << "Print: outputs 4: " << DetailedDebugString(outputs[4]);
    }

    {
        auto input_image = Const(
            scope, {{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}},
                    {{11, 11, 11}, {12, 12, 12}, {13, 13, 13}, {14, 14, 14}},
                    {{21, 21, 21}, {22, 22, 22}, {23, 23, 23}, {24, 24, 24}},
                    {{31, 31, 31}, {32, 32, 32}, {33, 33, 33}, {34, 34, 34}}});
        auto shape = Shape(scope, input_image);
        auto limit = Add(scope, Subtract(scope, shape, {2, 2, 3}), {1, 1, 1});
        auto offset =
            Mod(scope, RandomUniformInt(scope, Shape(scope, limit), 0, INT32_MAX),
                limit);
        LOG(INFO) << "Node building status: " << scope.status();

        auto ret_input_image =
            Slice(scope, Reshape(scope, input_image, {4, 4, 3}), offset, {2, 2, 3});
        LOG(INFO) << "Node building status: " << scope.status();

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status =
            session.Run({}, {ret_input_image, shape, limit, offset}, {}, &outputs);

        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
        LOG(INFO) << "Print: outputs 1: " << outputs[1].DebugString();
        LOG(INFO) << "Print: outputs 2: " << outputs[2].DebugString();
        LOG(INFO) << "Print: outputs 3: " << outputs[3].DebugString();
    }

    {
        Output input_image, real_image;
        std::tie(input_image, real_image) =
            LoadP2P(scope, Const(scope, "/tmp/data/facades/train/100.jpg"));
        std::tie(input_image, real_image) = ResizeP2P(
            scope, input_image, real_image, RESIZED_IMAGE_SIZE, RESIZED_IMAGE_SIZE);
        std::tie(input_image, real_image) =
            RandomCropP2P(scope, input_image, real_image);

        Output input_image_norm, real_image_norm;
        std::tie(input_image_norm, real_image_norm) =
            NormalizeP2P(scope, input_image, real_image);

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status = session.Run({}, {input_image, real_image}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
        LOG(INFO) << "Print: outputs 1: " << outputs[1].DebugString();

#ifdef ENABLE_OPENCV
        {
            cv::Mat mat(IMAGE_SIZE, IMAGE_SIZE, CV_32FC3,
                        outputs[0].flat<float>().data());
            // mat = mat / PIXEL_DEPTH;

            std::vector<cv::Mat> channels_bgr;
            cv::split(mat, channels_bgr);

            std::vector<cv::Mat> channels_rgb = {channels_bgr[2], channels_bgr[1],
                                                 channels_bgr[0]};
            cv::merge(channels_rgb, mat);

            // Save images in folder "/tmp/data/"
            cv::imwrite("/tmp/data/input_image.png", mat);
        }
        {
            cv::Mat mat(IMAGE_SIZE, IMAGE_SIZE, CV_32FC3,
                        outputs[1].flat<float>().data());
            // mat = mat / PIXEL_DEPTH;

            std::vector<cv::Mat> channels_bgr;
            cv::split(mat, channels_bgr);

            std::vector<cv::Mat> channels_rgb = {channels_bgr[2], channels_bgr[1],
                                                 channels_bgr[0]};
            cv::merge(channels_rgb, mat);

            // Save images in folder "/tmp/data/"
            cv::imwrite("/tmp/data/real_image.png", mat);
        }
#endif

        status = session.Run({}, {input_image_norm, real_image_norm}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0 input_image_norm: "
                  << outputs[0].DebugString();
        LOG(INFO) << "Print: outputs 1 real_image_norm: "
                  << outputs[1].DebugString();
    }

    {
        Output input_image, real_image;
        std::tie(input_image, real_image) =
            LoadImageTrainX(scope, Const(scope, "/tmp/data/facades/train/100.jpg"));

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status = session.Run({}, {input_image, real_image}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
        LOG(INFO) << "Print: outputs 1: " << outputs[1].DebugString();
    }

    {
        auto matching_files = MatchingFiles(scope, "/tmp/data/facades/train/*.jpg");

        // Prepare output_shapes
        vector<PartialTensorShape> output_shapes;
        output_shapes.emplace_back(tensorflow::PartialTensorShape({}));

        auto unstack = Unstack(scope, matching_files, 400);

        // TensorSliceDataset
        auto tensor_slice_dataset =
            TensorSliceDataset(scope, OutputList({matching_files}), output_shapes);

        vector<Tensor> outputs;
        ClientSession session(scope);

        // Status status = session.Run({}, unstack.output, {}, &outputs);
        Status status = session.Run({}, {tensor_slice_dataset}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
        // LOG(INFO) << "Print: outputs 1: " << outputs[1].DebugString();
        // LOG(INFO) << "Print: outputs 2: " << outputs[2].DebugString();
    }

    {
        auto input_image = Const(
            scope, {{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}},
                    {{11, 11, 11}, {12, 12, 12}, {13, 13, 13}, {14, 14, 14}},
                    {{21, 21, 21}, {22, 22, 22}, {23, 23, 23}, {24, 24, 24}},
                    {{31, 31, 31}, {32, 32, 32}, {33, 33, 33}, {34, 34, 34}}});
        auto shape = Shape(scope, input_image);

        Input input = input_image;
        const Tensor input_tensor = input.tensor();
        const TensorShape input_shape = input_tensor.shape();
        LOG(INFO) << "Print: input_shape.dim_size 0: " << input_shape.dim_size(0);
        LOG(INFO) << "Print: input_shape.dim_size 1: " << input_shape.dim_size(1);
        LOG(INFO) << "Print: input_shape.dim_size 2: " << input_shape.dim_size(2);

        vector<Tensor> outputs;
        ClientSession session(scope);

        Status status =
            session.Run({}, {shape}, {}, &outputs);
        LOG(INFO) << "Print: outputs 0: " << outputs[0].DebugString();
    }
}

#endif

#endif  // TENSORFLOW_EXAMPLES_CC_GAN_PIX2PIX_TEST_H_
