load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cmake_external(
    name = "openblas",
    cache_entries = {
        "BUILD_WITHOUT_LAPACK": "no",
        "NOFORTRAN": "on",
    },
    lib_source = "@openblas//:all",
    static_libraries = ["libopenblas.a"],
    cmake_options = ["j12"],
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
    deps = [":openblas"],
    cmake_options = ["j12"],
)

cc_binary(
    name = "EigenDemo",
    srcs = ["main.cc"],
    deps = [
        ":eigen",
    ],
)