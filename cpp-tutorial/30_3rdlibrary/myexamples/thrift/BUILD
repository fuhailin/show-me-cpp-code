fbthrift_compile(
    name = "echo",
    src = "echo.thrift",
    options = [
        "reflection",
    ],
    services = [
        "EchoService",
    ],
)

fbthrift_cc_library(
    name = "echo_lib",
    src = "echo.thrift",
    copts = [
        "-std=c++14",
    ],
    options = [
        "reflection",
    ],
    services = [
        "EchoService",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@fbthrift//:thriftcpp2",
    ],
)

cc_binary(
    name = "client",
    srcs = glob(["my_client.cpp"]),
    copts = ["-Iinclude"],
    linkopts = ["-lexpat"],
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_binary(
    name = "server",
    srcs = glob(["my_server.cpp"]),
    copts = ["-Iinclude"],
    linkopts = ["-lexpat"],
    deps = [
        "@apache_thrift//:thrift",
    ],
)
