"""A module defining the third party dependency rules"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def rules_cc_repo():
    COMMIT = "608c7b605fb844a20e96a3eddc9b49ad2542adab"
    maybe(
        http_archive,
        name = "rules_cc",
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://hub.fastgit.org/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_cc/archive/{commit}.zip".format(commit = COMMIT),
        ],
        strip_prefix = "rules_cc-" + COMMIT,
    )

def rules_foreign_cc_repo():
    COMMIT = "main"
    maybe(
        http_archive,
        name = "rules_foreign_cc",
        strip_prefix = "rules_foreign_cc-" + COMMIT,
        urls = [
            "https://github.com/bazelbuild/rules_foreign_cc/archive/{commit}.zip".format(commit = COMMIT),
        ],
    )

def rules_proto_repo():
    COMMIT = "84ba6ec814eebbf5312b2cc029256097ae0042c3"
    maybe(
        http_archive,
        name = "rules_proto",
        strip_prefix = "rules_proto-" + COMMIT,
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://hub.fastgit.org/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_proto/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
    )

def rules_boost_repo():
    COMMIT = "f734190672a17c0efcd0882d450dea2d6457e9fa"
    maybe(
        http_archive,
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://github.com.cnpmjs.org/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/nelhage/rules_boost/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rules_boost-" + COMMIT,
    )

# rules_java defines rules for generating Java code from Protocol Buffers.
def rules_java_repo():
    COMMIT = "6076aa3dd8a669d48abc3a1c282beeed1ecc68d2"
    maybe(
        http_archive,
        name = "rules_java",
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_java/archive/{commit}.tar.gz".format(commit = COMMIT),
            "https://github.com/bazelbuild/rules_java/archive/{commit}.tar.gz".format(commit = COMMIT),
        ],
        strip_prefix = "rules_java-" + COMMIT,
    )

def rules_jvm_repo():
    RULES_JVM_EXTERNAL_TAG = "4.0"
    RULES_JVM_EXTERNAL_SHA = "31701ad93dbfe544d597dbe62c9a1fdd76d81d8a9150c2bf1ecf928ecdf97169"
    maybe(
        http_archive,
        name = "rules_jvm_external",
        urls = [
            "https://github.com.cnpmjs.org/bazelbuild/rules_jvm_external/archive/%s.zip" % RULES_JVM_EXTERNAL_TAG,
            "https://github.com/bazelbuild/rules_jvm_external/archive/%s.zip" % RULES_JVM_EXTERNAL_TAG,
        ],
        strip_prefix = "rules_jvm_external-%s" % RULES_JVM_EXTERNAL_TAG,
    )
