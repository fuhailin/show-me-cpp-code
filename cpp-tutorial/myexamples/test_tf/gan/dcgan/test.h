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

#ifndef TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_TEST_H_
#define TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_TEST_H_

#include <string>
#include <vector>

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/dataset_ops_internal.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"

#include "tensorflow/examples/cc/gan/dcgan/const.h"

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

void test(const Scope& scope) {
  // Test SigmoidCrossEntropyWithLogits
  {
    auto logits = Const(scope, {{-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}});
    auto ones_like = OnesLike(scope, logits);
    auto scel = SigmoidCrossEntropyWithLogits(scope, ones_like, logits);
    auto result = ReduceMean(scope, scel, {0, 1});

    vector<Tensor> outputs;
    ClientSession session(scope);

    Status status = session.Run({}, {result}, {}, &outputs);

    LOG(INFO) << "Print: SigmoidCrossEntropyWithLogits result: "
              << outputs[0].DebugString();
  }

  // Test BatchNormalization
  {
    auto x = Const<float>(scope, {{-1.0, 2.0, 1.0}, {1.0, 1.0, 1.0}});
    auto mean = Const<float>(scope, {0.0f});
    auto variance = Const<float>(scope, {1.0f});
    auto offset = Const<float>(scope, {0.0f});
    auto scale = Const<float>(scope, {1.0f});
    auto variance_epsilon = Const<float>(scope, {0.001f});
    auto batchnorm = BatchNormalization(scope, x, mean, variance, offset, scale,
                                        variance_epsilon);

    vector<Tensor> outputs;
    ClientSession session(scope);

    Status status = session.Run({}, {batchnorm}, {}, &outputs);

    LOG(INFO) << "Print: BatchNormalization result: "
              << DetailedDebugString(outputs[0]);
  }

  // Test Dropout
  {
    auto x = Const<float>(scope, {{-1.0, 2.0, 1.0}, {1.0, 1.0, 1.0}});
    auto dropout = Dropout(scope, x, {0.3f});

    vector<Tensor> outputs;
    ClientSession session(scope);

    Status status = session.Run({}, {dropout}, {}, &outputs);

    LOG(INFO) << "Print: Dropout result: " << DetailedDebugString(outputs[0]);
  }

  // Test GlorotUniform
  {
    auto glorot_uniform = GlorotUniform(scope, {3, 4});

    vector<Tensor> outputs;
    ClientSession session(scope);

    Status status = session.Run({}, {glorot_uniform}, {}, &outputs);

    LOG(INFO) << "Print: GlorotUniform result: "
              << DetailedDebugString(outputs[0]);
  }

  // Test Conv2DTranspose
  {
    int batch_size = 1;

    // Const
    auto const1 = Const<float>(scope, 1.0f, {batch_size, 7, 7, 256});
    LOG(INFO) << "Node building status: " << scope.status();

    // Conv2DTranspose 1
    auto input_sizes = Const<int>(scope, {batch_size, 7, 7, 128});
    // filter, aka kernel
    auto filter = Variable(scope, {5, 5, 128, 256}, DT_FLOAT);
    auto random_value1 = GlorotUniform(scope, {5, 5, 128, 256});
    auto assign_filter = Assign(scope, filter, random_value1);

    // out_backprop, aka input. here it's reshape1
    auto deconv1 = Conv2DTranspose(scope, input_sizes, filter, const1,
                                   {1, 1, 1, 1}, "SAME");
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    TF_CHECK_OK(session.Run({assign_filter}, nullptr));
    TF_CHECK_OK(session.Run({}, {deconv1}, {}, &outputs));

    LOG(INFO) << "Print: Conv2DTranspose result: "
              << DetailedDebugString(outputs[0]);
  }

  // Test Moments #1
  {
    auto x = Const<float>(scope, {{1, 2, 3}, {4, 5, 6}});
    auto moments = Moments(scope, x, {0}, false);
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    TF_CHECK_OK(
        session.Run({}, {moments.mean, moments.variance}, {}, &outputs));

    LOG(INFO) << "Print: Moments #1 result: " << DetailedDebugString(outputs[0])
              << " - " << DetailedDebugString(outputs[1]);
  }
  // Test Moments #2
  {
    auto x = Const<float>(scope, {{1.2, 2.4, 3.5}, {10.8, 15.4, 32.1}});
    auto moments = Moments(scope, x, {0}, false);
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    TF_CHECK_OK(
        session.Run({}, {moments.mean, moments.variance}, {}, &outputs));

    LOG(INFO) << "Print: Moments #2 result: " << DetailedDebugString(outputs[0])
              << " - " << DetailedDebugString(outputs[1]);
  }
  // Test Moments #3
  {
    auto x = Const<float>(scope, {{-1.0, 2.0, 1.0}, {1.0, 1.0, 1.0}});
    auto moments = Moments(scope, x, {0}, false);
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    TF_CHECK_OK(
        session.Run({}, {moments.mean, moments.variance}, {}, &outputs));

    LOG(INFO) << "Print: Moments #3 result: " << DetailedDebugString(outputs[0])
              << " - " << DetailedDebugString(outputs[1]);
  }

  // Test decay
  {
    auto moving_mean = Variable(scope, {2, 3}, DT_FLOAT);
    TFAssign(scope, moving_mean, ZerosLike(scope, moving_mean));

    auto mean = Const<float>(scope, {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}});

    auto decay = Const<float>(scope, 1.0f - MOMENTUM, {});
    auto update_delta1 = Multiply(scope, Sub(scope, moving_mean, mean), decay);
    auto update_moving_mean = AssignSub(scope, moving_mean, update_delta1);

    vector<Tensor> outputs;
    ClientSession session(scope);
    session.InitializeVariables(scope);

    for (int i = 0; i < 3; i++) {
      TF_CHECK_OK(session.Run({}, {update_moving_mean}, {}, &outputs));

      LOG(INFO) << "Print: decay step #" << i
                << ", result: " << DetailedDebugString(outputs[0]);
    }
  }

  // Test TFBatchNormalization
  {
    // Const
    auto x = Const<float>(scope, {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}});
    LOG(INFO) << "Node building status: " << scope.status();

    auto variance_epsilon = Const<float>(scope, {0.001f});

    TFBatchNormalization bn_op(scope, {3});
    auto bn = bn_op.Build(scope, x, {0}, variance_epsilon, true);
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    session.InitializeVariables(scope);

    for (int i = 0; i < 1; i++) {
      TF_CHECK_OK(session.Run({}, {bn}, {}, &outputs));

      LOG(INFO) << "Print: TFBatchNormalization training step #" << i
                << ", result: " << DetailedDebugString(outputs[0]);

      // Run update ops
      session.RunUpdateOps(scope);
    }

    auto bn2 = bn_op.Build(scope, x, {0}, variance_epsilon, false);
    LOG(INFO) << "Node building status: " << scope.status();

    TF_CHECK_OK(session.Run({}, {bn2}, {}, &outputs));
    LOG(INFO) << "Print: TFBatchNormalization inference result: "
              << DetailedDebugString(outputs[0]);
  }

  // Test TFFusedBatchNorm
  {
    // Const
    auto x = Const<float>(scope, {{{{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}},
                                   {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}}},
                                  {{{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}},
                                   {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}}}});
    LOG(INFO) << "Node building status: " << scope.status();

    TFFusedBatchNorm bn_op(scope, {3});
    auto bn = bn_op.Build(scope, x, 0.001f, true);
    LOG(INFO) << "Node building status: " << scope.status();

    vector<Tensor> outputs;
    ClientSession session(scope);

    session.InitializeVariables(scope);

    for (int i = 0; i < 1; i++) {
      TF_CHECK_OK(session.Run({}, {bn}, {}, &outputs));

      LOG(INFO) << "Print: TFFusedBatchNorm training step #" << i
                << ", result: " << DetailedDebugString(outputs[0]);

      // Run update ops
      session.RunUpdateOps(scope);
    }

    auto bn2 = bn_op.Build(scope, x, 0.001f, false);
    LOG(INFO) << "Node building status: " << scope.status();

    TF_CHECK_OK(session.Run({}, {bn2}, {}, &outputs));
    LOG(INFO) << "Print: TFFusedBatchNorm inference result: "
              << DetailedDebugString(outputs[0]);
  }

  // Test Models
  {
    // Models
    auto generator = Generator(scope);
    auto discriminator = Discriminator(scope);

    // For inference
    const int num_examples_to_generate = 1;
    auto generator_inference =
        generator.Build(scope, num_examples_to_generate, false);
    auto discriminator_inference = discriminator.Build(
        scope, generator_inference, num_examples_to_generate);

    vector<Tensor> outputs;
    ClientSession session(scope);

    session.InitializeVariables(scope);

    // Run Test
    TF_CHECK_OK(session.Run({}, {generator_inference, discriminator_inference},
                            &outputs));
    LOG(INFO) << "Print discriminator output 0: " << outputs[0].DebugString();
    LOG(INFO) << "Print discriminator output 1: " << outputs[1].DebugString();
  }

  // Test TFFusedBatchNorm
  {
    // Const
    auto x = Const<float>(scope, {{{{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}},
                                   {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}}},
                                  {{{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}},
                                   {{-1.0, 2.0, 1.0}, {1.0, 2.0, 3.0}}}});
    LOG(INFO) << "Node building status: " << scope.status();

    auto y = Div(scope, x, {2.0f});

    vector<Tensor> outputs;
    ClientSession session(scope);

    Status status = session.Run({}, {y}, {}, &outputs);

    LOG(INFO) << "Print: Div result: "
              << DetailedDebugString(outputs[0]);
  }
}

#endif

#endif  // TENSORFLOW_EXAMPLES_CC_GAN_DCGAN_TEST_H_
