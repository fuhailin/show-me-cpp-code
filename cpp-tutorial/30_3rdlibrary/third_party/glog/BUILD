load("@bazel_skylib//rules:build_test.bzl", "build_test")

# exports_files(
#     [
#         "BUILD.glog.bazel",
#     ],
#     visibility = ["//visibility:public"],
# )

build_test(
    name = "build_test",
    targets = [
        "@com_github_google_glog//:glog",
    ],
    visibility = ["//:__pkg__"],
)
