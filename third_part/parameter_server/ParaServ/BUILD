# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "ParaServ_lib",
    srcs = glob(["ParaServThrift/*.cpp"]),
    hdrs = glob(["ParaServThrift/*.h"]),
    includes = ["ParaServThrift"],
    visibility = ["//visibility:public"],
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_library(
    name = "ParaServThrift",
    srcs = glob(["ParaServThrift/*.cpp"]),
    hdrs = glob(["ParaServThrift/*.h"]),
)

cc_binary(
    name = "ParaServ",
    srcs = [
        "include/assert_exit.h",
        "include/config.h",
        "include/external_util.h",
        "include/gproxy_server_register.h",
        "include/logger.hpp",
        "include/para_serv_handler.h",
        "include/para_serv_op.h",
        "include/port_holder.h",
        "include/psconfigure.h",
        "include/replication.h",
        "include/timer.h",
        "src/external_util.cpp",
        "src/logger.cpp",
        "src/main.cpp",
        "src/para_serv_handler.cpp",
        "src/para_serv_op.cpp",
        "src/psconfigure.cpp",
        "src/replication.cpp",
    ],
    copts = [
        "-Iparameter_server/ParaServ/include",
        "-Iparameter_server/ParaServ/ParaServThrift",
        "-ggdb3",
        "-DNDBUG",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-ldl",
        "-lz",
        "-llz4",
        "-lbz2",
        "-lzstd",
        "-lsnappy",
        # "-lstdc++",
    ],
    deps = [
        ":ParaServThrift",
        ":prometheus_util",
        "//parameter_server/common",
        "@apache_thrift//:thrift",
        "@boost",
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_github_jupp0r_prometheus_cpp//push",
        "@cpp3rd_lib//tcmcp",
        "@cpp3rd_lib//util",
        "@cpp3rd_lib//zk_client",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
        "@oneTBB//:tbb",
        "@spdlog",
    ],
)

cc_binary(
    name = "ps_client",
    srcs = glob(
        [
            "ParaServThrift/*.cpp",
            "ParaServThrift/*.h",
            "client/ps_client.cpp",
            "include/*.h",
            "include/*.hpp",
            "src/*.cpp",
        ],
        exclude = ["src/main.cpp"],
    ),
    copts = [
        "-IParaServ/include",
        "-IParaServ/ParaServThrift",
        "-ggdb3",
        "-DNDBUG",
    ],
    linkopts = [
        "-L/usr/local/lib",
        "-ldl",
        "-lz",
        "-llz4",
        "-lbz2",
        "-lzstd",
        "-lsnappy",
        "-lstdc++",
    ],
    deps = [
        "@apache_thrift//:thrift",
        "@boost",
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@com_github_jupp0r_prometheus_cpp//push",
        "@cpp3rd_lib//tcmcp",
        "@cpp3rd_lib//util",
        "@cpp3rd_lib//zk_client",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
    ],
)

cc_binary(
    name = "test",
    srcs = glob([
        "thrift/MatrixRand.cpp",
        "client/check_mencpy.cpp",
    ]),
    copts = [
        "-IParaServ/thrift",
        "-ggdb3",
        "-DNDBUG",
    ],
    deps = [
        "@apache_thrift//:thrift",
        "@boost",
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@cpp3rd_lib//util",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
    ],
)

cc_library(
    name = "prometheus_util",
    srcs = ["prometheus_util.cpp"],
    hdrs = ["prometheus_util.h"],
    deps = [
        "@com_github_jupp0r_prometheus_cpp//push",
    ],
)
