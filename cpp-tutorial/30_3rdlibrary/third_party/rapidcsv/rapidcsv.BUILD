load("@rules_cc//cc:defs.bzl", "cc_library")

# load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
# load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "rapidcsv",
    srcs = ["rapidcsv.h"],
    visibility = ["//main:__pkg__"],
)

# cmake_external(
#     name = "rapidcsv",
#     # Probably this variable should be set by default.
#     # Apparently, it needs to be set for shared libraries on Mac OS
#     # cache_entries = {
#     #     "CMAKE_MACOSX_RPATH": "True",
#     # },
#     lib_source = "@d99kris_rapidcsv//:src/rapidcsv.h ",
# )
