load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "folly",
    srcs = glob(
        ["folly/**/*.cpp"],
        exclude = [
            "folly/**/test/**",
            "folly/**/example/**",
            "folly/python/**",
            "folly/tools/**",
            "folly/experimental/exception_tracer/**",
            "folly/experimental/TestUtil.cpp",
            "folly/experimental/io/HugePageUtil.cpp",
            "folly/experimental/JSONSchemaTester.cpp",
        ],
    ),
    hdrs = glob(["folly/**/*.h"]),
    copts = ["-std=c++17"],
    includes = ["."],
    linkopts = ["-ldl"],
    deps = [
        "@boost//:algorithm",
        "@boost//:container",
        "@boost//:context",
        "@boost//:crc",
        "@boost//:filesystem",
        "@boost//:function_types",
        "@boost//:functional",
        "@boost//:interprocess",
        "@boost//:intrusive",
        "@boost//:multi_index",
        "@boost//:operators",
        "@boost//:preprocessor",
        "@boost//:program_options",
        "@boost//:regex",
        "@boost//:thread",
        "@boost//:variant",
        "@liburing//:liburing",
        "@com_github_fmtlib_fmt//:fmt",
        "@double-conversion//:double-conversion",
        "@com_github_google_glog//:glog",
        "@com_google_googletest//:gtest",
        "@snappy//:snappy",
        "@libevent//:libevent",
        # "@com_github_libsodium//:sodium",
        # "@com_pagure_libaio//:libaio",
        # "@libiberty",
        "@zlib//:zlib",
        # "@org_openssl//:crypto",
        "@openssl//:openssl",
        # "@org_xz_xz//:xz",
        # "@rules_3rd//third_party/folly/extra:config",
    ],
)
