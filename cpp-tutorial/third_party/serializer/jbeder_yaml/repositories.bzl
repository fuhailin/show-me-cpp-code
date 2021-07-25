load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def repo(commit = "0.6.3"):
    maybe(
        http_archive,
        name = "jbeder_yaml",
        urls = [
            "https://github.com.cnpmjs.org/jbeder/yaml-cpp/archive/yaml-cpp-{commit}.tar.gz".format(commit = commit),
        ],
        strip_prefix = "yaml-cpp-yaml-cpp-{commit}".format(commit = commit),
        build_file = Label("//third_party/serializer/jbeder_yaml:jbeder_yaml.BUILD"),
    )
