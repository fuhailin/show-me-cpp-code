cc_library(
    name = "object_detection",
    srcs = ["get_prediction.cpp"],
    hdrs = ["saved_model_loader.h"],
    copts = [
        "-std=c++14",
    ],
    deps = [
        "@com_github_opencv//:opencv",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
    ],
)
