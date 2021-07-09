load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

cmake(
    name = "eigen",
    # These options help CMake to find prebuilt OpenBLAS, which will be copied into
    # $EXT_BUILD_DEPS/openblas by the cmake_external script
    cache_entries = {
        "BLAS_VENDOR": "OpenBLAS",
        "BLAS_LIBRARIES": "$EXT_BUILD_DEPS/openblas/lib/libopenblas.a",
    },
    lib_source = ":all_srcs",
    out_headers_only = True,
    # Dependency on other cmake_external rule; can also depend on cc_import, cc_library rules
    deps = ["@openblas"],
)
