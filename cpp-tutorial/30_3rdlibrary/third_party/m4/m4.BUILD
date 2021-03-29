load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds for me on Linux, did not work MAC
configure_make(
    name = "m4",
    configure_env_vars = {
        "AR": "",
    },
    binaries = [
        "m4",
    ],
    configure_options = [
        "--disable-nls",
    ],
    lib_source = "@org_gnu_m4//:all",
)
