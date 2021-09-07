cc_binary(
    name = "main",
    srcs = ["test-bignum-dtoa.cc"],
    # copts = [
    #     "-std=c++14",
    # ],
    deps = [
        ":cctest",
        "@com_github_google_double_conversion//:double-conversion",
    ],
)

cc_library(
    name = "cctest",
    hdrs = ["cctest.h"],
    deps = [
        "@com_github_google_double_conversion//:double-conversion",
    ],
)
