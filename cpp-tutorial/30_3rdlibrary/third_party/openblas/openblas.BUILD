load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "openblas",
    build_args = [
        "--verbose",
        # "--",  # <- Pass remaining options to the native tool.
        "-j 10",
    ],
    cache_entries = {
        "BUILD_WITHOUT_LAPACK": "no",
        "NOFORTRAN": "on",
    },
    lib_source = "@openblas//:all",
    out_static_libs = ["libopenblas.a"],
    visibility = ["//visibility:public"],
)
