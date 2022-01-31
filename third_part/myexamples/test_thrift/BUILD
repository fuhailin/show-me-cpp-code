cc_library(
    name = "Calculator_lib",
    srcs = glob(["gen-cpp/*.cc"]),
    hdrs = glob(["gen-cpp/*.h"]),
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_binary(
    name = "client",
    srcs = ["CppClient.cpp"],
    copts = ["-Imyexamples/test_thrift/gen-cpp"],
    deps = [
        ":Calculator_lib",
        "@apache_thrift//:thrift",
    ],
)

cc_binary(
    name = "server",
    srcs = ["CppServer.cpp"],
    copts = ["-Imyexamples/test_thrift/gen-cpp"],
    deps = [
        ":Calculator_lib",
        "@apache_thrift//:thrift",
    ],
)
