load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@boost//:array",
        "@boost//:asio",
        "@boost//:context",
        "@boost//:filesystem",
        "@boost//:format",
        "@boost//:iostreams",
        # "@boost//:log",
        "@boost//:random",
        "@boost//:test",
        "@boost//:unordered",
        "@boost//:uuid",
        "@boost//:locale",
        "@boost//:json",
        "@boost//:date_time",
    ],
    visibility = ["//:__pkg__"],
)
