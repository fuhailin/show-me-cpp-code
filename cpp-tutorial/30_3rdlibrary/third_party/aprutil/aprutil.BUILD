load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds only for me on Linux
configure_make(
    name = "aprutil",
    # configure_env_vars = {
    #     "AR": "",
    # },
    configure_options = [
        "--with-apr=$EXT_BUILD_DEPS/apr",
        "--with-expat=$EXT_BUILD_DEPS/expat",
    ],
    lib_source = "@apache_aprutil//:all",
    static_libraries = ["libaprutil-1.a"],
    deps = [
        "@apache_apr//:apr",
        "@libexpat//:expat",
    ],
)
