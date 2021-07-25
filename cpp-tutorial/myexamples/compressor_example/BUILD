cc_binary(
    name = "zlib_usage_example",
    srcs = ["zlib_example.cpp"],
    deps = ["@zlib"],
)

cc_library(
    name = "zstd_common",
    hdrs = ["common.h"],
    deps = [
        "@zstd",
    ],
)

cc_binary(
    name = "zstd_demo",
    srcs = ["simple_compression.cc"],
    deps = [
        ":zstd_common",
        "@zstd",
    ],
)
