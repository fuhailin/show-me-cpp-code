load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
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
    lib_source = ":all_srcs",
    out_static_libs = ["libexpat.a"],
    # deps = [
    #     "@apache_apr//:apr",
    # ],
)
