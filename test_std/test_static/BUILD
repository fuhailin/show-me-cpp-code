cc_library(
    name = "liba",
    srcs = ["a.cc"],
    # strip_include_prefix = "test_std/test_static",
)

cc_binary(
    name = "main",
    srcs = ["b.cc"],
    deps = [":liba"],
)
