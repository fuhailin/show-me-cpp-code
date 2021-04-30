cc_binary(
    name = "main",
    srcs = ["test-bignum-dtoa.cc"],
    # copts = [
    #     "-std=c++14",
    # ],
    deps = [
        ":cctest",
        "@double-conversion//:double-conversion",
    ],
)

cc_library(
    name = "cctest",
    hdrs = ["cctest.h"],
    deps = [
        "@double-conversion//:double-conversion",
    ],
)
