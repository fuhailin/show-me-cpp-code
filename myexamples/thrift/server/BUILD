cc_binary(
    name = "echo_server",
    srcs = [
        "demo.cc",
        "demo.h",
        "echo_server.cc",
        "echo_service.cc",
        "echo_service.h",
    ],
    copts = [
        "-std=c++17",
    ],
    deps = [
        "//myexamples/thrift/if:echo_lib",
        "@com_github_facebook_folly//:folly",
        "@fbthrift//:http2",
    ],
)
