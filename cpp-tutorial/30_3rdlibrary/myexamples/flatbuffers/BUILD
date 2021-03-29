load("@com_github_google_flatbuffers//:build_defs.bzl", "flatbuffer_cc_library")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "sample_binary",
    srcs = ["sample_binary.cpp"],
    deps = [
        ":monster",
    ],
)

flatbuffer_cc_library(
    name = "monster",
    srcs = ["monster.fbs"],
)
