load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "nlohmann_json_lib",
    hdrs = glob([
        "include/nlohmann/**/*.hpp",
    ]),
    copts = [
        "-I external/nlohmann_json_lib",
    ],
    alwayslink = 1,
)

cc_library(
    name = "json",
    includes = ["include"],
    deps = ["nlohmann_json_lib"],
)
