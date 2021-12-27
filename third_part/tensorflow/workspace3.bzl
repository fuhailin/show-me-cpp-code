"""TensorFlow workspace initialization. Consult the WORKSPACE on how to use it."""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("//third_party:tf_runtime/workspace.bzl", tf_runtime = "repo")
load("//third_party/llvm:workspace.bzl", llvm = "repo")

def workspace():
    http_archive(
        name = "io_bazel_rules_closure",
        sha256 = "5b00383d08dd71f28503736db0500b6fb4dda47489ff5fc6bed42557c07c6ba9",
        strip_prefix = "rules_closure-308b05b2419edb5c8ee0471b67a40403df940149",
        urls = [
            "https://storage.googleapis.com/mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/308b05b2419edb5c8ee0471b67a40403df940149.tar.gz",
            "https://github.com/bazelbuild/rules_closure/archive/308b05b2419edb5c8ee0471b67a40403df940149.tar.gz",  # 2019-06-13
        ],
    )

    http_archive(
        name = "tf_toolchains",
        sha256 = "d72b2e52baf0592f5b94347b128ef75422fc22f63dfcf2d5fd46bc732cab052b",
        strip_prefix = "toolchains-1.3.0",
        urls = [
            "http://mirror.tensorflow.org/github.com/tensorflow/toolchains/archive/v1.3.0.tar.gz",
            "https://github.com/tensorflow/toolchains/archive/v1.3.0.tar.gz",
        ],
    )

    tf_runtime()

    # https://github.com/bazelbuild/bazel-skylib/releases
    http_archive(
        name = "bazel_skylib",
        sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
        urls = [
            "https://storage.googleapis.com/mirror.tensorflow.org/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        ],
    )

    # TODO(rostam): Delete after the release of Bazel built-in cc_shared_library.
    http_archive(
        name = "rules_pkg",
        sha256 = "352c090cc3d3f9a6b4e676cf42a6047c16824959b438895a76c2989c6d7c246a",
        urls = [
            "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.5/rules_pkg-0.2.5.tar.gz",
            "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.2.5/rules_pkg-0.2.5.tar.gz",
        ],
    )

    http_archive(
        name = "rules_foreign_cc",
        sha256 = "69023642d5781c68911beda769f91fcbc8ca48711db935a75da7f6536b65047f",
        strip_prefix = "rules_foreign_cc-0.6.0",
        urls = [
            "https://github.com/bazelbuild/rules_foreign_cc/archive/0.6.0.tar.gz",
        ],
    )

    git_repository(
        name = "rules_compressor",
        branch = "main",
        remote = "https://github.com/fuhailin/rules_compressor.git",
    )

    # native.local_repository(
    #     name = "ps-lite",
    #     path = "/root/fuhailin/projects/ps-lite",
    # )
    git_repository(
        name = "ps-lite",
        branch = "master",
        remote = "https://github.com/fuhailin/ps-lite.git",
    )

    # Load the raw llvm-project.  llvm does not have build rules set up by default,
    # but provides a script for setting up build rules via overlays.
    llvm("llvm-raw")

    http_archive(
        name = "com_grail_bazel_compdb",
        strip_prefix = "bazel-compilation-database-0.5.2",
        urls = ["https://github.com/grailbio/bazel-compilation-database/archive/0.5.2.tar.gz"],
    )

    # native.local_repository(
    #     name = "cpp3rd_lib",
    #     path = "/Users/vincent/Documents/projects/cpp3rd_lib",
    # )
    git_repository(
        name = "cpp3rd_lib",
        branch = "master",
        remote = "https://gitee.com/fuhailin/cpp3rd_lib.git",
    )

# Alias so it can be loaded without assigning to a different symbol to prevent
# shadowing previous loads and trigger a buildifier warning.
tf_workspace3 = workspace