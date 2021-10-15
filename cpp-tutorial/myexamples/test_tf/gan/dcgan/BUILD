cc_binary(
    name = "dcgan",
    srcs = [
        "const.h",
        "dcgan.cc",
        "model.cc",
        "model.h",
        "test.h",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
    ],
)

cc_binary(
    name = "dcgan_multi_gpus",
    srcs = [
        "const.h",
        "dcgan_multi_gpus.cc",
        "model.cc",
        "model.h",
        "test.h",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
    ],
)
