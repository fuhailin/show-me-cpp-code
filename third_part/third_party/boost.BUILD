load("@rules_foreign_cc//foreign_cc:defs.bzl", "boost_build")

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:private"],
)

boost_build(
    name = "boost",
    bootstrap_options = ["--without-icu"],
    lib_source = ":all_srcs",
    out_shared_libs = [
        "libboost_filesystem.so.1.76.0",
        "libboost_program_options.so.1.76.0",
        "libboost_regex.so.1.76.0",
        "libboost_system.so.1.76.0",
        "libboost_thread.so.1.76.0",
        "libboost_context.so.1.76.0",
    ],
    user_options = [
        "-j `nproc`",
        "--with-filesystem",
        "--with-program_options",
        "--with-regex",
        "--with-system",
        "--with-thread",
        "--with-context",
        "variant=release",
        "link=shared",
        "threading=multi",
    ],
    visibility = ["//visibility:public"],
)
