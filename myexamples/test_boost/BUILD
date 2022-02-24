cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-std=c++11",
    ],
    deps = [
        "@boost",
    ],
)

cc_binary(
    name = "context_test",
    srcs = ["context_test.cc"],
    copts = [
        "-std=c++11",
    ],
    deps = [
        "@boost",
    ],
)

cc_binary(
    name = "bind",
    srcs = ["test_bind.cc"],
    copts = [
        "-std=c++11",
    ],
    deps = [
        "@boost",
    ],
)

cc_test(
    name = "iostreams_test",
    size = "small",
    srcs = ["iostreams_test.cc"],
    linkopts = [
        "-lz",
        "-lzstd",
    ],
    deps = [
        "@boost//:iostreams",
    ],
)
