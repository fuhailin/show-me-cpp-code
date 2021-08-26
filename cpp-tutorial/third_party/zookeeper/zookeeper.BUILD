# vim: ft=bzl

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all_srcs",
    srcs = glob(
        include = ["**"],
        exclude = ["config/docker/**"],
    ),
)

cmake(
    name = "zookeeper_client",
    build_args = [
        "-j `nproc`",
    ],
    lib_source = ":all_srcs",
    visibility = ["//visibility:public"],
)
