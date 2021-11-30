cc_binary(
    name = "mnist",
    srcs = [
        "mnist.cc",
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

cc_binary(
    name = "mnist_rkz",
    srcs = [
        "mnist_rkz.cc",
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
