cc_binary(
    name = "echo_client",
    srcs = [
        "echo_client.cc",
    ],
    copts = [
        "-std=c++14",
    ],
    deps = [
        "//myexamples/thrift/if:echo_lib",
        "@com_github_facebook_folly//:folly",
        "@fbthrift//:http2",
        "@fbthrift//:thriftperfutil",
    ],
)
