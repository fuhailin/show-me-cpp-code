load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "eigen",
    build_args = [
        "--verbose",
        "-j 10",
    ],
    cache_entries = {
        "BLAS_LIBRARIES": "$EXT_BUILD_DEPS/openblas/lib/libopenblas.a",
        "BLA_VENDOR": "OpenBLAS",
    },
    lib_source = "@eigen//:all",
    out_headers_only = True,
    out_include_dir = "include/eigen3",
    visibility = ["//visibility:public"],
    deps = ["@openblas"],
)
