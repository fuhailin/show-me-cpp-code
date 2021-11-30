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
// Example of GeneratorDataset op with FUNCTION
// Author: Rock Zhuang
// Date  : Jan 08, 2019
//

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

// Constructs a scalar tensor with 'val'.
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
    const Tensor kTwo = AsScalar<int64>(2);
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

int main() {
    Scope root = Scope::NewRootScope();

    auto x = Placeholder(root.WithOpName("x"), DT_FLOAT, Placeholder::Shape({1}));
    auto b = Placeholder(root.WithOpName("b"), DT_FLOAT, Placeholder::Shape({1}));

    FunctionDefLibrary proto;
    *proto.add_function() = INIT();
    *proto.add_function() = NEXT();
    *proto.add_function() = FINALIZE();
    root.graph()->AddFunctionLibrary(proto);

    NameAttrList init_fn;
    init_fn.set_name("INIT");
    (*init_fn.mutable_attr())["T"].set_type(DT_FLOAT);

    NameAttrList next_fn;
    next_fn.set_name("NEXT");
    (*next_fn.mutable_attr())["T"].set_type(DT_FLOAT);

    NameAttrList final_fn;
    final_fn.set_name("FINALIZE");
    (*final_fn.mutable_attr())["T"].set_type(DT_FLOAT);

    auto generator_dataset = ops::internal::GeneratorDataset(
        root.WithOpName("GeneratorDataset"), std::initializer_list<Input>{x},
        std::initializer_list<Input>{b}, std::initializer_list<Input>{}, init_fn,
        next_fn, final_fn, {DT_FLOAT}, {{1}});

    std::vector<tensorflow::Tensor> outputs;
    tensorflow::ClientSession session(root);

    tensorflow::Tensor x_tensor1(tensorflow::DT_FLOAT,
                                 tensorflow::TensorShape({1}));
    x_tensor1.vec<float>()(0) = 2;

    tensorflow::Tensor b_tensor1(tensorflow::DT_FLOAT,
                                 tensorflow::TensorShape({1}));
    b_tensor1.vec<float>()(0) = 3;

    Output iterator_output =
        Iterator(root, "iterator1", "", std::initializer_list<DataType>{DT_FLOAT},
                 std::initializer_list<PartialTensorShape>{{}});
    Operation make_iterator_op =
        MakeIterator(root, generator_dataset, iterator_output);
    auto iterator_get_next = IteratorGetNext(
        root, iterator_output, std::initializer_list<DataType>{DT_FLOAT},
        std::initializer_list<PartialTensorShape>{{}});

    // Run make_iterator first
    TF_CHECK_OK(session.Run({{x, x_tensor1}, {b, b_tensor1}}, {},
                            {make_iterator_op}, nullptr));
    TF_CHECK_OK(session.Run({}, iterator_get_next.components, {}, &outputs));
    LOG(INFO) << "Print iterator_get_next, debug: " << outputs[0].DebugString();

    for (int i = 0; i < 10; i++) {
        TF_CHECK_OK(session.Run({{x, x_tensor1}, {b, outputs[0]}}, {},
                                {make_iterator_op},
                                nullptr));  // INIT will be invoked again
        TF_CHECK_OK(session.Run({}, iterator_get_next.components, {}, &outputs));
        LOG(INFO) << "Print iterator_get_next, debug: " << outputs[0].DebugString();
    }

    return 0;
}
