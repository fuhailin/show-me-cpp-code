load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_proto_library(
    name = "test_cc_proto",
    deps = [":test_proto"],
)

cc_proto_library(
    name = "test2_cc_proto",
    deps = [":test2_proto"],
)

proto_library(
    name = "test_proto",
    srcs = ["test.proto"],
)

proto_library(
    name = "test2_proto",
    srcs = ["test2.proto"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [":test_cc_proto"],
)
