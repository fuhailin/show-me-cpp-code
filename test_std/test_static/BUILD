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
            "@com_google_googletest//:gtest_main",
        ],
    )
    for f in glob([
        "*.cc",
        "*.cpp",
    ])
]
