"""A module defining the third party dependency opencv"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    maybe(
        http_archive,
        name = "opencv",
        build_file = Label("//third_party/opencv:opencv.BUILD"),
        strip_prefix = "opencv-4.3.0",
        urls = [
            "https://github.com.cnpmjs.org/opencv/opencv/archive/4.3.0.zip",
            "https://github.com/opencv/opencv/archive/4.3.0.zip",
        ],
    )
