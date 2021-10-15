"""A module defining the third party dependency opencv"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "4.5.3"):
    maybe(
        http_archive,
        name = "com_github_opencv",
        strip_prefix = "opencv-{}".format(commit),
        urls = [
            "https://github.com/opencv/opencv/archive/refs/tags/{}.tar.gz".format(commit),
        ],
        build_file = Label("//third_party/opencv:opencv.BUILD"),
    )

    # maybe(
    #     native.new_local_repository,
    #     name = "com_github_opencv",
    #     build_file = "//third_party/opencv:opencv.BUILD",
    #     path = "/Users/vincent/Downloads/opencv-4.5.3",
    # )
