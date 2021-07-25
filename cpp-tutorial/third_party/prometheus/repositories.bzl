load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo():
    COMMIT = "0.12.2"
    maybe(
        http_archive,
        name = "com_github_jupp0r_prometheus_cpp",
        urls = [
            "https://github.com/jupp0r/prometheus-cpp/archive/v{commit}.zip".format(commit = COMMIT),
        ],
        strip_prefix = "prometheus-cpp-" + COMMIT,
    )
