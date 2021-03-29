# vim: ft=bzl

package(
    default_visibility = ["//visibility:public"],
)

[
    cc_test(
        name = "%s" % f[0:f.rfind(".")],
        srcs = [
            "%s" % f,
        ],
        copts = [
            "-std=gnu++17",
            "-w",
        ],
        deps = [
            "@com_google_googletest//:gtest_main",
            "//include:ListNode"
        ],
    )
    for f in glob(["*.cc"])
]