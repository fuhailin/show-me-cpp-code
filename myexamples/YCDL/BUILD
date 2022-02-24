filegroup(
    name = "ps_headers",
    srcs = glob([
        "include/*.h",
    ]),
)

cc_library(
    name = "headers",
    hdrs = [
        ":ps_headers",
    ],
    strip_include_prefix = "/myexamples/YCDL/include",
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "lr_uci",
    srcs = [
        "src/lr_uci.cpp",
    ],
    deps = [
        ":headers",
        "@boost",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
        "@ps-lite//:ps-lite",
    ],
)

cc_binary(
    name = "network",
    srcs = [
        "src/network.cpp",
    ],
    copts = ["-Iinclude"],
    deps = [
        ":headers",
        "@boost",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
        "@ps-lite//:ps-lite",
    ],
)
