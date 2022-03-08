# vim: ft=bzl

package(
    default_visibility = ["//visibility:public"],
)

[
    cc_binary(
        # name = "%s" % f[0:f.rfind(".")],
        name = f.split(".")[0],
        srcs = [
            "%s" % f,
        ],
        copts = [
            "-std=gnu++17",
            "-w",
        ],
        deps = [
            "//bits:stdcxx",
            "//include:LinkedList",
            "//include:TreeNode",
            "@com_google_googletest//:gtest_main",
        ],
    )
    for f in glob(["*.cc"])
]

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
            "//bits:stdcxx",
            "//include:LinkedList",
            "//include:TreeNode",
            "@com_google_googletest//:gtest_main",
        ],
    )
    for f in glob([
        "*.cc",
        "*.cpp",
    ])
]
