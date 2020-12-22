cc_binary(
    name = "client",
    srcs = glob(["main/my_client.cpp"]),
    deps = [
        "@cpp3rd_lib//thrift_0.12.0:thrift",
    ],
    copts = ["-Iinclude"],
    linkopts = ["-lexpat"]
)

cc_binary(
    name = "server",
    srcs = glob(["main/my_server.cpp"]),
    deps = [
        "@cpp3rd_lib//thrift_0.12.0:thrift",
    ],
    copts = ["-Iinclude"],
    linkopts = ["-lexpat"]
)