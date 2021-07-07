load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "nlohmann_json.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@nlohmann_json//:nlohmann_json",
    ],
    visibility = ["//:__pkg__"],
)
