# buildifier: disable=module-docstring
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

# load("//bison:bison_repositories.bzl", "bison_repositories")
load("//cares:cares_repositories.bzl", "cares_repositories")
load("//curl:curl_repositories.bzl", "curl_repositories")

# load("//gn:gn_repositories.bzl", "gn_repositories")
load("//iconv:iconv_repositories.bzl", "iconv_repositories")
load("//libgit2:libgit2_repositories.bzl", "libgit2_repositories")

# load("//libpng:libpng_repositories.bzl", "libpng_repositories")
load("//libssh2:libssh2_repositories.bzl", "libssh2_repositories")
load("//openssl:openssl_repositories.bzl", "openssl_repositories")
load("//pcre:pcre_repositories.bzl", "pcre_repositories")
load("//zlib:zlib_repositories.bzl", "zlib_repositories")
load("//cityhash:cityhash_repositories.bzl", "cityhash_repositories")
load("//openblas:openblas_repositories.bzl", "openblas_repositories")
load("//eigen:eigen_repositories.bzl", "eigen_repositories")
load("//libevent:libevent_repositories.bzl", "libevent_repositories")
load("//gtest:gtest_repositories.bzl", "gtest_repositories")
load("//gflags:gflags_repositories.bzl", "gflags_repositories")
load("//glog:glog_repositories.bzl", "glog_repositories")
load("//abseil:abseil_repositories.bzl", "abseil_repositories")
load("//zeromq:zeromq_repositories.bzl", "zeromq_repositories")

def repositories():
    """Load all repositories needed for the targets of rules_foreign_cc_examples_third_party"""

    # bison_repositories()
    cares_repositories()
    curl_repositories()

    # gn_repositories()
    iconv_repositories()
    libgit2_repositories()

    # libpng_repositories()
    libssh2_repositories()
    openssl_repositories()
    pcre_repositories()
    zlib_repositories()
    cityhash_repositories()
    openblas_repositories()
    eigen_repositories()
    libevent_repositories()
    gtest_repositories()
    gflags_repositories()
    glog_repositories()
    abseil_repositories()
    zeromq_repositories()

    maybe(
        http_archive,
        name = "rules_cc",
        strip_prefix = "rules_cc-b1c40e1de81913a3c40e5948f78719c28152486d",
        url = "https://github.com/bazelbuild/rules_cc/archive/b1c40e1de81913a3c40e5948f78719c28152486d.zip",
        sha256 = "d0c573b94a6ef20ef6ff20154a23d0efcb409fb0e1ff0979cec318dfe42f0cdd",
        type = "zip",
    )
