# vim: ft=bzl
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# test passed for Linux
configure_make(
    name = "jemalloc",
    autogen = True,
    configure_in_place = True,
    # configure_command = "configure",
    configure_options = [],
    install_prefix = "lib",
    lib_source = "@jemalloc//:all",
    out_include_dir = "include",
    out_lib_dir = "lib",
    static_libraries = [
        "libjemalloc.a",
    ],
    visibility = ["//visibility:public"],
)
