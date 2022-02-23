cc_library(
    name = "data_set",
    srcs = ["data_set.cc"],
    hdrs = ["data_set.h"],
)

cc_binary(
    name = "toydnn",
    srcs = [
        "toydnn.cc",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        ":data_set",
        "@com_github_gflags_gflags//:gflags",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
    ],
)
