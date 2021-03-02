load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake_external(
    name = "openblas",
    cache_entries = {
        "BUILD_WITHOUT_LAPACK": "no",
        "NOFORTRAN": "on",
    },
    lib_source = "@openblas//:all",
    static_libraries = ["libopenblas.a"],
    visibility = ["//visibility:public"],
)