load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

configure_make(
    name = "jemalloc",
    configure_command = "autogen.sh",
    configure_in_place = True,
    configure_options = [
        "--disable-debug",
        "--with-jemalloc-prefix=",
        "--enable-prof",
        "--enable-prof-libunwind",
    ],
    lib_source = ":all_srcs",
    out_shared_libs = ["libjemalloc.so"],
    # out_static_libs = ["libjemalloc.so"],
)
