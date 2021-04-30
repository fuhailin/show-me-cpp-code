cc_library(
    name = "folly",
    # srcs = [
    #     "folly/FileUtil.cpp",
    #     "folly/ScopeGuard.cpp",
    #     "folly/container/detail/F14Table.cpp",
    #     "folly/lang/Assume.cpp",
    #     "folly/lang/SafeAssert.cpp",
    #     "folly/net/NetOps.cpp",
    # ],
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
    hdrs = glob([
        "folly/**/*.h",
    ]),
    copts = [
        "-std=c++14",
    ],
    defines = [
        "FOLLY_NO_CONFIG",
        "FOLLY_HAVE_MEMRCHR",
        "FOLLY_HAVE_SENDMMSG",
        "FOLLY_HAVE_RECVMMSG",
    ],
    includes = [""],
    visibility = ["//visibility:public"],
    deps = [
        # "@com_github_google_double_conversion//:double-conversion",
        "@double-conversion//:double-conversion",
        "@com_github_google_glog//:glog",
        "@com_github_fmtlib_fmt//:fmt",
    ],
)
