cc_binary(
    name = "testtf",
    srcs = [
        "testtf.cc",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        # "@com_github_gflags_gflags//:gflags",
        "@cppbuilt_lib//DeepRec:tensorflow_cc",
        "@cppbuilt_lib//DeepRec:tensorflow_framework",
        "@com_google_protobuf//:protobuf",
    ],
)
