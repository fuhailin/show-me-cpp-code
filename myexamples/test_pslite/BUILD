package(default_visibility = ["//visibility:public"])

cc_test(
    name = "client",
    srcs = [
        "lr_ps.cc",
    ],
    deps = [
        "@ps-lite//:ps-lite",
    ],
)

cc_test(
    name = "server",
    srcs = [
        "ps.cpp",
    ],
    deps = [
        "@ps-lite//:ps-lite",
    ],
)

cc_binary(
    name = "connection",
    srcs = [
        "tests/test_connection.cc",
    ],
    deps = [
        "@ps-lite//:ps-lite",
    ],
)

cc_binary(
    name = "test_simple_app",
    srcs = [
        "test_simple_app.cc",
    ],
    deps = [
        "@ps-lite//:ps-lite",
    ],
)
