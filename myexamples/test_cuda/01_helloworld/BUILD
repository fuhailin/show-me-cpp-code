load("@local_config_cuda//cuda:build_defs.bzl", "cuda_library")

cuda_library(
    name = "demo",
    srcs = ["demo.cu"],
    visibility = ["//visibility:public"],
    deps = [
        "@local_config_cuda//cuda",
    ],
)
