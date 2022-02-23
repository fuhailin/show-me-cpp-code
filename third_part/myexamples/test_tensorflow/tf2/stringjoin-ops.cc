#include <string>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/cc/ops/string_ops.h"
#include "tensorflow/core/framework/tensor.h"

using namespace std;

// Simple hello world using TensorFlows

// The sample demonstrates how to
// - create various ops (Const & StringJoin)
// - pass them around for e.g. StringJoin takes an list of other ops
// - pass the final ops to the session
// - get the result of the session
// - a simple peek inside the output using the DebugString & by flattening it

int main(int argc, char **argv) {
    // create a root scope
    auto scope = tensorflow::Scope::NewRootScope();

    // define various constans/inputs on which we
    // will perform an operation
    auto hello = tensorflow::ops::Const(scope, std::string("hello"));
    auto space = tensorflow::ops::Const(scope, std::string(" "));
    auto world = tensorflow::ops::Const(scope, std::string("world !"));

    // StringJoin operation
    auto joinOp = tensorflow::ops::StringJoin(scope, {hello, space, world});

    // create a session that takes our
    // scope as the root scope
    tensorflow::ClientSession session(scope);

    // Run
    std::vector<tensorflow::Tensor> outputs;
    TF_CHECK_OK(session.Run({joinOp}, &outputs));

    // See our output using DebugString that tells
    // more information about the tensor
    std::cout << "DebugString -> " << outputs[0].DebugString() << std::endl;

    // we can also get the underlying data by calling flat
    // auto tmp = outputs[0].flat<std::string>()(0);
    // std::cout << "Underlying Scalar value -> " << outputs[0].flat<std::string>() << std::endl;
    std::cout << "shape -> " << outputs[0].shape() << std::endl;
    std::cout << "dtype -> " << outputs[0].dtype() << std::endl;
    std::cout << "NumElements -> " << outputs[0].NumElements() << std::endl;
    std::cout << "TotalBytes -> " << outputs[0].TotalBytes() << std::endl;

    // auto str = outputs[0].data();

    auto data = outputs[0].data();
    int size = outputs[0].TotalBytes();
    string tmp(size, 'a');
    std::memcpy(&tmp[0], data, sizeof(char) * size);
    // string
    // std::cout << "values:" <<
    // char *str = "Hello world";
    // cout << hex << &str << endl;         //输出的是str指针变量的地址
    // cout << hex << (void *)str << endl;  //输出的是str指针的值

    cout << "size: " << tmp.size() <<"  value: " << tmp << endl;                 //输出的是字符串str

    return 0;
}
