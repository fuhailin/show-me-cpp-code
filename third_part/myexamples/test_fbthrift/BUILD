# Copyright 2019 curoky(cccuroky@gmail.com).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@org_tensorflow//third_party/fbthrift:build_defs.bzl", "fbthrift_library")
load("@org_tensorflow//tensorflow:copts.bzl", "TEST_CPP_COPTS", "TEST_LINKOPTS")

fbthrift_library(
    name = "mock_fbthrift",
    srcs = ["mock.thrift"],
    include_prefix = "myexamples/test_fbthrift",
    lang_options = ",json,reflection,any,frozen2",
    services = ["EchoService"],
)

cc_test(
    name = "example",
    testonly = False,
    srcs = glob([
        "*.h",
        "*.cc",
    ]) + [
        ":mock_fbthrift",
    ],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "@com_github_apache_thrift//:thrift",
        "@com_github_facebook_fbthrift//:fbthrift",
    ],
)
