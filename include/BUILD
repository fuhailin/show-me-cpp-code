package(default_visibility = ["//visibility:public"])

_COPTS = [
    "-std=gnu++2a",
]

cc_library(
    name = "LinkedList",
    srcs = [
        "LinkedList.cc",
    ],
    hdrs = [
        "LinkedList.h",
    ],
    copts = _COPTS,
    # strip_include_prefix = "include",
)

cc_library(
    name = "TreeNode",
    hdrs = [
        "TreeNode.h",
    ],
    copts = _COPTS,
)

cc_library(
    name = "cache",
    hdrs = [
        "cache.h",
    ],
)

[
    cc_binary(
        name = "%s" % f[0:f.rfind(".")],
        srcs = [
            "%s" % f,
        ],
        copts = [
            "-std=gnu++17",
            "-w",
        ],
        deps = [
            ":cache",
            "//bits:stdcxx",
            "@com_google_googletest//:gtest",
            "@com_google_googletest//:gtest_main",
        ],
    )
    for f in glob([
        "*.cpp",
    ])
]
