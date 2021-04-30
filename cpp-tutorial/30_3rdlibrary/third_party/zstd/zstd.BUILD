# vim: ft=bzl

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# test passed for Linux
cmake(
    name = "zstd",
    build_args = [
        "--verbose",
        "-j 12",
    ],
    lib_source = "@zstd//:all",
    # out_include_dir = "include",
    # out_lib_dir = "lib",
    out_static_libs = [
        "libzstd.a",
    ],
    # make_commands = [
    #     # The correct path to the ninja tool is detected from the selected ninja_toolchain.
    #     # and "ninja" will be replaced with that path if needed
    #     "cmake ..",
    #     "make",
    # ],
    working_directory = "build/cmake",
)
