cc_binary(
    name = "test_spdlog",
    srcs = [
        "test_spdlog.cpp",
    ],
    # copts = [
    #     "-std=c++14",
    # ],
    deps = [
        "@spdlog",
    ],
)

cc_test(
    name = "test_glog",
    size = "small",
    srcs = [
        "test_glog.cc",
    ],
    # copts = [
    #     "-std=c++14",
    # ],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "test_glog1",
    srcs = [
        "test_glog1.cc",
    ],
    deps = [
        "@com_github_google_glog//:glog",
    ],
)
