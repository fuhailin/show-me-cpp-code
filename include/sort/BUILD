cc_library(
    name = "merge_sort",
    srcs = ["merge_sort.cc"],
    hdrs = ["merge_sort.h"],
    # strip_include_prefix = "include/sort",
    # include_prefix = "include/sort",
    # includes = ["include/sort"],
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
            ":merge_sort",
            "@com_google_googletest//:gtest",
            "@com_google_googletest//:gtest_main",
        ],
    )
    for f in glob([
        "*.cpp",
    ])
]
