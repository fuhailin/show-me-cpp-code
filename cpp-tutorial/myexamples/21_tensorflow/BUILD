load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["testtf.cc"],
    # defines = ["USE_TCMCP", "USE_TENSORFLOW"],
    linkopts = [
        "-lexpat",
        "-fopenmp",
        "-lcurl",
        "-lpthread",
    ],
    deps = [
        "@com_google_protobuf//:protoc",
        "@tensorflow//:tensorflow_cc",
        "@tensorflow//:tensorflow_framework",
    ],
)
