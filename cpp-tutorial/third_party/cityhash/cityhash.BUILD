load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

configure_make(
    name = "cityhash",
    configure_env_vars = {
        "AR": "",
    },
    configure_options = [
        "--enable-shared=no",
    ],
    install_prefix = "lib",
    lib_source = "@cityhash//:all",
    out_lib_dir = "lib",
    out_static_libs = ["libcityhash.a"],
    visibility = ["//visibility:public"],
)
