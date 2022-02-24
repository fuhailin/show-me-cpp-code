cc_binary(
    name = "sort",
    srcs = ["std_sort_test.cc"],
)

cc_binary(
    name = "sort1",
    srcs = ["std_sort_test1.cc"],
    deps = [
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "partial_sort",
    srcs = ["partial_sort_test.cc"],
    copts = [
        "-std=c++17",
        "//bits:stdcxx",
    ],
)
