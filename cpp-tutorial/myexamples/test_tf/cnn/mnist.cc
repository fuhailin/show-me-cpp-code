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
// C++ implementation of LeNet-5-like convolutional MNIST model example
// The correspoding python version:
// https://github.com/tensorflow/models/tree/master/tutorials/image/mnist
//
// Author: Rock Zhuang
// Date  : Jan 23, 2019
//

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace tensorflow::ops::internal;
using namespace std;

// #define VERBOSE 1
// #define TESTING 1

// Adjustable Parameters
#define VALIDATION_SIZE 5000  // Size of the validation set.
#define BATCH_SIZE 64
#define BATCHES_PER_EPOCHS 859  // (55000 / BATCH_SIZE) = 859 max
#define NUM_EPOCHS 10
#define EVAL_BATCH_SIZE 64
#define EVAL_FREQUENCY 100  // Number of steps between evaluations.
#define DECAY_RATE 0.95f
#define MOMENTUM 0.9f
#define BASE_LEARNING_RATE 0.01f

// Not to change
#define IMAGE_SIZE 28
#define NUM_CHANNELS 1
#define PIXEL_DEPTH 255.0f
#define NUM_LABELS 10
#define INPUTS_HEADER_BYTES 16
#define LABELS_HEADER_BYTES 8
#define NUM_IMAGES (BATCH_SIZE * BATCHES_PER_EPOCHS)  // 55000 images max

static string DetailedDebugString(const Tensor& tensor) {
    return strings::StrCat("Tensor<type: ", DataTypeString(tensor.dtype()),
                           " shape: ", tensor.shape().DebugString(),
                           " values: ", tensor.SummarizeValue(-1, true), ">");
}

// dropout
// Python Code {
// keep_prob = 1 - rate
// # uniform [keep_prob, 1.0 + keep_prob)
// random_tensor = keep_prob
// random_tensor += random_ops.random_uniform(
//     noise_shape, seed=seed, dtype=x.dtype)
// # 0. if [keep_prob, 1.0) and 1. if [1.0, 1.0 + keep_prob)
// binary_tensor = math_ops.floor(random_tensor)
// ret = math_ops.divide(x, keep_prob) * binary_tensor
// }
static Status Dropout(const Scope& scope, const Input x, const int rate,
                      Output& dropout) {
    float keep_prob = 1 - rate;
    auto random_value5 = RandomUniform(scope, Shape(scope, x), DT_FLOAT);
    auto random_tensor =
        Add(scope, random_value5, Const<float>(scope, {keep_prob}));
    auto binary_tensor = Floor(scope, random_tensor);
    auto result = Multiply(scope, Div(scope, x, Const<float>(scope, {keep_prob})),
                           binary_tensor);

    dropout = result.z;

    return scope.status();
}

int main() {
    Scope scope = Scope::NewRootScope();

    //
    // Parse images and labels files into tensors
    //

    // Read file and decompress data
    auto inputs_contents = ReadFile(
        scope,
        Const<tensorflow::tstring>(scope, "/tmp/data/train-images-idx3-ubyte.gz",
                                   TensorShape({})));
    auto inputs_decode_compressed = DecodeCompressed(
        scope, inputs_contents, DecodeCompressed::CompressionType("GZIP"));

    auto labels_contents = ReadFile(
        scope,
        Const<tensorflow::tstring>(scope, "/tmp/data/train-labels-idx1-ubyte.gz",
                                   TensorShape({})));
    auto labels_decode_compressed = DecodeCompressed(
        scope, labels_contents, DecodeCompressed::CompressionType("GZIP"));

    vector<Tensor> outputs;
    ClientSession session(scope);

    // Load data into tensors
    Tensor inputs(DT_FLOAT, TensorShape({NUM_IMAGES, IMAGE_SIZE, IMAGE_SIZE,
                                         NUM_CHANNELS}));
    Tensor labels(DT_INT64, TensorShape({NUM_IMAGES}));

    Status status = session.Run(
        {}, {inputs_decode_compressed, labels_decode_compressed}, {}, &outputs);
    if (status.ok()) {
        // inputs
        std::string inputs_str = outputs[0].scalar<tensorflow::tstring>()();
        const char* inputs_str_data = inputs_str.c_str();

        float* inputs_data = inputs.tensor<float, 4>().data();
        int count = NUM_IMAGES * IMAGE_SIZE * IMAGE_SIZE * NUM_CHANNELS;
        for (int i = 0; i < count; i++) {
            float data =
                (unsigned char)(*(inputs_str_data + INPUTS_HEADER_BYTES + i));
            data = (data - (PIXEL_DEPTH / 2.0f)) / PIXEL_DEPTH;

            inputs_data[i] = data;
        }

        // labels
        std::string labels_str = outputs[1].scalar<tensorflow::tstring>()();
        const char* labels_str_data = labels_str.c_str();

        // for(int i = 0; i < NUM_IMAGES; i++) {
        //   std::cout << (int)labels_str_data[i] << ", ";
        // }

        int64* labels_data = labels.vec<int64>().data();
        for (int i = 0; i < NUM_IMAGES; i++) {
            labels_data[i] =
                (unsigned char)(*(labels_str_data + LABELS_HEADER_BYTES + i));
        }
    } else {
        LOG(INFO) << "Print: status: " << status;

        return -1;
    }

#ifdef VERBOSE
    LOG(INFO) << "Print: inputs: " << inputs.DebugString();
    LOG(INFO) << "Print: inputs: " << labels.DebugString();
#endif

    //
    // Convolutional Net
    //

    auto ph_inputs = Placeholder(
        scope, DT_FLOAT,
        Placeholder::Shape({BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS}));
    auto ph_labels =
        Placeholder(scope, DT_INT64, Placeholder::Shape({BATCH_SIZE}));

    // Trainable variables
    auto rate = Const(scope, {0.1f});

    auto conv1_weights = Variable(scope, {5, 5, NUM_CHANNELS, 32}, DT_FLOAT);
    auto random_value =
        TruncatedNormal(scope, {5, 5, NUM_CHANNELS, 32}, DT_FLOAT);
    auto assign_conv1_weights =
        Assign(scope, conv1_weights, Multiply(scope, random_value, rate));

    auto conv1_biases = Variable(scope, {32}, DT_FLOAT);
    Tensor b_zero_tensor(DT_FLOAT, TensorShape({32}));
    b_zero_tensor.vec<float>().setZero();
    auto assign_conv1_biases = Assign(scope, conv1_biases, b_zero_tensor);

    auto conv2_weights = Variable(scope, {5, 5, 32, 64}, DT_FLOAT);
    auto random_value2 = TruncatedNormal(scope, {5, 5, 32, 64}, DT_FLOAT);
    auto assign_conv2_weights =
        Assign(scope, conv2_weights, Multiply(scope, random_value2, rate));

    auto conv2_biases = Variable(scope, {64}, DT_FLOAT);
    auto assign_conv2_biases =
        Assign(scope, conv2_biases, Const<float>(scope, 0.1f, TensorShape({64})));

    int s1 = IMAGE_SIZE;
    s1 = s1 / 4;
    s1 = std::pow(s1, 2) * 64;
    auto fc1_weights = Variable(scope, {s1, 512}, DT_FLOAT);
    auto random_value3 = TruncatedNormal(scope, {s1, 512}, DT_FLOAT);
    auto assign_fc1_weights =
        Assign(scope, fc1_weights, Multiply(scope, random_value3, rate));

    auto fc1_biases = Variable(scope, {512}, DT_FLOAT);
    auto assign_fc1_biases =
        Assign(scope, fc1_biases, Const<float>(scope, 0.1f, TensorShape({512})));

    auto fc2_weights = Variable(scope, {512, NUM_LABELS}, DT_FLOAT);
    auto random_value4 = TruncatedNormal(scope, {512, NUM_LABELS}, DT_FLOAT);
    auto assign_fc2_weights =
        Assign(scope, fc2_weights, Multiply(scope, random_value4, rate));

    auto fc2_biases = Variable(scope, {NUM_LABELS}, DT_FLOAT);
    auto assign_fc2_biases = Assign(
        scope, fc2_biases, Const<float>(scope, 0.1f, TensorShape({NUM_LABELS})));

    // Gradient accum parameters start here
    auto accum_conv1_weights =
        Variable(scope, {5, 5, NUM_CHANNELS, 32}, DT_FLOAT);
    auto assign_accum_conv1_weights =
        Assign(scope, accum_conv1_weights, ZerosLike(scope, conv1_weights));

    auto accum_conv1_biases = Variable(scope, {32}, DT_FLOAT);
    auto assign_accum_conv1_biases =
        Assign(scope, accum_conv1_biases, ZerosLike(scope, conv1_biases));

    auto accum_conv2_weights = Variable(scope, {5, 5, 32, 64}, DT_FLOAT);
    auto assign_accum_conv2_weights =
        Assign(scope, accum_conv2_weights, ZerosLike(scope, conv2_weights));

    auto accum_conv2_biases = Variable(scope, {64}, DT_FLOAT);
    auto assign_accum_conv2_biases =
        Assign(scope, accum_conv2_biases, ZerosLike(scope, conv2_biases));

    auto accum_fc1_weights = Variable(scope, {s1, 512}, DT_FLOAT);
    auto assign_accum_fc1_weights =
        Assign(scope, accum_fc1_weights, ZerosLike(scope, fc1_weights));

    auto accum_fc1_biases = Variable(scope, {512}, DT_FLOAT);
    auto assign_accum_fc1_biases =
        Assign(scope, accum_fc1_biases, ZerosLike(scope, fc1_biases));

    auto accum_fc2_weights = Variable(scope, {512, NUM_LABELS}, DT_FLOAT);
    auto assign_accum_fc2_weights =
        Assign(scope, accum_fc2_weights, ZerosLike(scope, fc2_weights));

    auto accum_fc2_biases = Variable(scope, {NUM_LABELS}, DT_FLOAT);
    auto assign_accum_fc2_biases =
        Assign(scope, accum_fc2_biases, ZerosLike(scope, fc2_biases));

    // Initialize variables
    TF_CHECK_OK(session.Run(
        {assign_conv1_weights, assign_conv1_biases, assign_conv2_weights,
         assign_conv2_biases, assign_fc1_weights, assign_fc1_biases,
         assign_fc2_weights, assign_fc2_biases},
        nullptr));
    TF_CHECK_OK(
        session.Run({assign_accum_conv1_weights, assign_accum_conv1_biases,
                     assign_accum_conv2_weights, assign_accum_conv2_biases,
                     assign_accum_fc1_weights, assign_accum_fc1_biases,
                     assign_accum_fc2_weights, assign_accum_fc2_biases},
                    nullptr));

    // Convnet Model begin
    auto conv2d_1 = Conv2D(scope, ph_inputs, conv1_weights,
                           gtl::ArraySlice<int>{1, 1, 1, 1}, "SAME");
    LOG(INFO) << "Node building status: " << scope.status();

    auto relu_1 = Relu(scope, BiasAdd(scope, conv2d_1, conv1_biases));
    LOG(INFO) << "Node building status: " << scope.status();

    auto max_pool_1 = MaxPool(scope, relu_1, gtl::ArraySlice<int>{1, 2, 2, 1},
                              gtl::ArraySlice<int>{1, 2, 2, 1}, "SAME");
    LOG(INFO) << "Node building status: " << scope.status();

    auto conv2d_2 = Conv2D(scope, max_pool_1, conv2_weights,
                           gtl::ArraySlice<int>{1, 1, 1, 1}, "SAME");
    LOG(INFO) << "Node building status: " << scope.status();

    auto relu_2 = Relu(scope, BiasAdd(scope, conv2d_2, conv2_biases));
    LOG(INFO) << "Node building status: " << scope.status();

    auto max_pool_2 = MaxPool(scope, relu_2, gtl::ArraySlice<int>{1, 2, 2, 1},
                              gtl::ArraySlice<int>{1, 2, 2, 1}, "SAME");
    LOG(INFO) << "Node building status: " << scope.status();

    // reshape
    auto reshape1 = Reshape(scope, max_pool_2, {BATCH_SIZE, s1});
    LOG(INFO) << "Node building status: " << scope.status();

    //
    auto hidden =
        Relu(scope, Add(scope, MatMul(scope, reshape1, fc1_weights), fc1_biases));
    LOG(INFO) << "Node building status: " << scope.status();

    // dropout
    Output dropout_output;
    if (!Dropout(scope, hidden, 0.5f, dropout_output).ok()) {
        LOG(ERROR) << "-----------------------------------------status: "
                   << scope.status();

        return scope.status().code();
    }

    // model output
    auto logits =
        Add(scope, MatMul(scope, dropout_output, fc2_weights), fc2_biases);
    // Convnet Model ends

    // loss
    auto sscewl = SparseSoftmaxCrossEntropyWithLogits(scope, logits, ph_labels);
    LOG(INFO) << "Node building status: " << scope.status();

    auto reduce_mean = ReduceMean(scope, sscewl.loss, {0});
    LOG(INFO) << "Node building status: " << scope.status();

    auto regularization =
        AddN(scope, initializer_list<Input>{
                        L2Loss(scope, fc1_weights), L2Loss(scope, fc1_biases),
                        L2Loss(scope, fc2_weights), L2Loss(scope, fc2_biases)});
    LOG(INFO) << "Node building status: " << scope.status();

    float f1 = 5e-4;
    auto loss = Add(scope, reduce_mean,
                    Multiply(scope, regularization, Const<float>(scope, {f1})));
    LOG(INFO) << "Node building status: " << scope.status();

    std::vector<Output> grad_outputs;
    TF_CHECK_OK(AddSymbolicGradients(
        scope, {loss},
        {conv1_weights, conv2_weights, fc1_weights, fc2_weights, conv1_biases,
         conv2_biases, fc1_biases, fc2_biases},
        &grad_outputs));
    LOG(INFO) << "Node building status: " << scope.status();

    // update the weights and bias using gradient descent
    auto ph_lr = Placeholder(scope, DT_FLOAT, Placeholder::Shape({}));

    auto apply_conv1_weights =
        ApplyMomentum(scope, conv1_weights, accum_conv1_weights, ph_lr,
                      grad_outputs[0], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_conv2_weights =
        ApplyMomentum(scope, conv2_weights, accum_conv2_weights, ph_lr,
                      grad_outputs[1], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_fc1_weights =
        ApplyMomentum(scope, fc1_weights, accum_fc1_weights, ph_lr,
                      grad_outputs[2], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_fc2_weights =
        ApplyMomentum(scope, fc2_weights, accum_fc2_weights, ph_lr,
                      grad_outputs[3], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_conv1_biases =
        ApplyMomentum(scope, conv1_biases, accum_conv1_biases, ph_lr,
                      grad_outputs[4], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_conv2_biases =
        ApplyMomentum(scope, conv2_biases, accum_conv2_biases, ph_lr,
                      grad_outputs[5], Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_fc1_biases =
        ApplyMomentum(scope, fc1_biases, accum_fc1_biases, ph_lr, grad_outputs[6],
                      Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();
    auto apply_fc2_biases =
        ApplyMomentum(scope, fc2_biases, accum_fc2_biases, ph_lr, grad_outputs[7],
                      Cast(scope, MOMENTUM, DT_FLOAT));
    LOG(INFO) << "Node building status: " << scope.status();

    int global_step = 0;

    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) {
        // update when each epoch
        float decayed_learning_rate =
            BASE_LEARNING_RATE * std::pow(DECAY_RATE, epoch);
        Tensor lr_tensor(decayed_learning_rate);

        for (int bidx = 0; bidx < BATCHES_PER_EPOCHS; bidx++) {
            // Input X
            Tensor x_tensor;
            CHECK(x_tensor.CopyFrom(
                inputs.Slice(bidx * BATCH_SIZE, (bidx + 1) * BATCH_SIZE),
                TensorShape({BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS})));

            // Labels
            Tensor y_tensor;
            CHECK(y_tensor.CopyFrom(
                labels.Slice(bidx * BATCH_SIZE, (bidx + 1) * BATCH_SIZE),
                TensorShape({BATCH_SIZE})));

            // Run
            vector<Tensor> outputs;
            TF_CHECK_OK(session.Run(
                {{ph_inputs, x_tensor}, {ph_labels, y_tensor}, {ph_lr, lr_tensor}},
                {loss, apply_conv1_weights, apply_conv2_weights, apply_fc1_weights,
                 apply_fc2_weights, apply_conv1_biases, apply_conv2_biases,
                 apply_fc1_biases, apply_fc2_biases},
                {}, &outputs));

            if (global_step % EVAL_FREQUENCY == 0) {
                LOG(INFO) << "Print step: " << global_step
                          << ", decayed_learning_rate: " << decayed_learning_rate
                          << ", loss: " << outputs[0].DebugString();
            }

            global_step++;
        }
    }

    return 0;
}
