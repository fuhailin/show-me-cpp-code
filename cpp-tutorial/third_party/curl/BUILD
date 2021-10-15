load("@bazel_skylib//rules:build_test.bzl", "build_test")

build_test(
    name = "build_test",
    targets = [
        "@com_github_curl//:libcurl",
        "@com_github_curl//:libcurl_openssl",
    ],
    visibility = ["//:__pkg__"],
)
