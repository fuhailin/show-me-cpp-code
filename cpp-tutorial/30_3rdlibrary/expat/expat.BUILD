load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds only for me on Linux
configure_make(
    name = "expat",
    autogen = True,
    autogen_command = "buildconf.sh",
    # configure_env_vars = {
    #     "AR": "",
    # },
    # configure_options = [
    #     "--with-apr=$EXT_BUILD_DEPS/apr",
    # ],
    lib_source = "@libexpat//:all",
    static_libraries = ["libexpat.a"],
    # deps = [
    #     "@apache_apr//:apr",
    # ],
)
