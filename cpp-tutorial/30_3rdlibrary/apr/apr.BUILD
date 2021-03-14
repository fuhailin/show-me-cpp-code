load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds only for me on Linux
configure_make(
    name = "apr",
    # configure_env_vars = {
    #     "AR": "",
    # },
    configure_options = [
        "--enable-shared=no",
        "--with-pic",
    ],
    lib_source = "@apache_apr//:all",
    static_libraries = ["libapr-1.a"],
)
