load("@bazel_skylib//rules:build_test.bzl", "build_test")

exports_files(
    [
        "terarkdb.BUILD",
    ],
    visibility = ["//visibility:public"],
)

build_test(
    name = "build_test",
    targets = [
        "@com_github_facebook_terarkdb//:terarkdb",
        # "@com_github_facebook_terarkdb//:terarkdb_tools_lib",
        # "@com_github_facebook_terarkdb//:db_stress",
    ],
    visibility = ["//:__pkg__"],
)
