load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

cmake(
    name = "folly",
    build_args = [
        "--verbose",
        "-j `nproc`",
    ],
    # env_vars = {
    #     "Boost_INCLUDE_DIR": "$EXT_BUILD_DEPS/include/",
    #     # "Boost_INCLUDE_DIR": "$$EXT_BUILD_DEPS$$",
    # },
    cache_entries = {
        "CMAKE_INCLUDE_PATH": "$EXT_BUILD_DEPS/include/:$EXT_BUILD_DEPS/include/boost/",
        "CMAKE_LIBRARY_PATH": "$EXT_BUILD_DEPS/lib/",
    },
    lib_source = "@com_github_facebook_folly//:all_srcs",
    deps = [
        # "@boost//:context",
        # "@boost//:filesystem",
        # "@boost//:program_options",
        # "@boost//:regex",
        # "@boost//:system",
        # "@boost//:thread",
        "@boost",
        "@double-conversion//:double-conversion",
    ],
)
