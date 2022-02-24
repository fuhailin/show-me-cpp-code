load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_java//java:defs.bzl", "java_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

# Convention:
# A cc_proto_library that wraps a proto_library named foo_proto
# should be called foo_cc_proto.
cc_proto_library(
    name = "example_cc_proto",
    deps = [":example_proto"],
)

proto_library(
    name = "example_proto",
    srcs = ["example.proto"],
    deps = [":feature_proto"],
    visibility = ["//__pkg__"],
)

proto_library(
    name = "feature_proto",
    srcs = ["feature.proto"],
)
