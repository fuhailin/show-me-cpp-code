load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "oneTBB",
    build_args = [
        "--verbose",
        # "--",  # <- Pass remaining options to the native tool.
        "-j `nproc`",
    ],
    # cache_entries = {
    #     "BUILD_WITHOUT_LAPACK": "no",
    #     "NOFORTRAN": "on",
    # },
    lib_source = "@oneTBB//:all",
    out_static_libs = [
        "libtbb.a",
        "libtbbmalloc.a",
    ],
    visibility = ["//visibility:public"],
)
