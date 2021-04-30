load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "pslite",
    srcs = glob([
        "src/**/*.cpp",
    ]),
    hdrs = glob([
        "**/*.h",
    ]) + glob([
        "include/**/*.(h|hpp)",
    ]),
    includes = ["include"],
)
