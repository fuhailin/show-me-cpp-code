load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake_external(
    name = "eigen",
    cache_entries = {
        "BLAS_LIBRARIES": "$EXT_BUILD_DEPS/openblas/lib/libopenblas.a",
        "BLA_VENDOR": "OpenBLAS",
    },
    headers_only = True,
    lib_source = "@eigen//:all",
    out_include_dir = "include/eigen3",
    deps = ["@openblas"],
    visibility = ["//visibility:public"],
)