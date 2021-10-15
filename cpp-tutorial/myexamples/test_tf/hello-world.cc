#include <iostream>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"

using namespace tensorflow;
using namespace tensorflow::ops;

int main() {
    Scope root = Scope::NewRootScope();

    // Matrix A = [3 2; -1 0]
    auto A = Const(root, {{3.f, 2.f}, {-1.f, 0.f}});
    // Vector b = [3 5]
    auto b = Const(root, {{3.f, 5.f}});
    // v = Ab^T
    auto v = MatMul(root.WithOpName("v"), A, b, MatMul::TransposeB(true));

    std::vector<Tensor> outputs;
    ClientSession session(root);

    // Run and fetch v
    TF_CHECK_OK(session.Run({v}, &outputs));
    std::cout << "tensorflow session run ok" << std::endl;
    // Expect outputs[0] == [19; -3]
    std::cout << "DebugString -> " << outputs[0].DebugString() << std::endl;
    std::cout << outputs[0].matrix<float>();
    std::cout << "Underlying Scalar value -> " << outputs[0].flat<float>() << std::endl;
    return 0;
}
