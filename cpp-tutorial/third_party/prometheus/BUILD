load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_github_jupp0r_prometheus_cpp//push",
    ],
    visibility = ["//:__pkg__"],
)
