# pybind11_bazel implementation
load("@pybind11_bazel//:build_defs.bzl", "pybind_library")

pybind_library(
    name = "mycpplib",
    hdrs = glob(["mycpplib/*.hpp"]),
    includes = ["."],
    visibility = ["//visibility:public"],
)
