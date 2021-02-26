load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "main",
    srcs = ["hello.cpp"],
    deps = [
        "@boost//:locale",
    ],
)

cc_test(
    name = "any_test",
    size = "small",
    srcs = ["any_test.cc"],
    deps = [
        "@boost//:any",
    ],
)