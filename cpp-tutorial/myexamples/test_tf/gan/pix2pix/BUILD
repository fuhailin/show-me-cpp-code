cc_binary(
    name = "pix2pix",
    srcs = [
        "const.h",
        "function.cc",
        "function.h",
        "model.cc",
        "model.h",
        "pix2pix.cc",
        "test.h",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        # "@com_github_gflags_gflags//:gflags",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
        "@com_github_opencv//:opencv",
    ],
)
