# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_binary(
    name = "PSProxy",
    srcs = glob([
        "include/*.h",
        "src/*.cpp",
        "gProxy/*.h",
        "gProxy/*.cpp",
        "module/*.h",
        "module/*.cpp",
    ]),
    copts = [
        "-IPSProxy/gProxy",
        "-IPSProxy/include",
        "-IPSProxy/module",
    ],
    linkopts = [
        "-lstdc++",
        "-pthread",
        "-lexpat",
    ],
    deps = [
        "//ParaServ:ParaServ_lib",
        "//common",
        "@apache_thrift//:thrift",
        "@boost",
        "@cityhash",
        "@cpp3rd_lib//log4cxx_v0.11.0-RC2:log4cxx",
        "@cpp3rd_lib//tcmcp",
        "@cpp3rd_lib//zk_client",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
        "@spdlog",
    ],
)

cc_binary(
    name = "proxy_client",
    srcs = glob([
        "client/*.cpp",
    ]),
    copts = [
    ],
    deps = [
        "@cityhash",
        "@cpp3rd_lib//tcmcp",
    ],
)
