# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "server_lib",
    srcs = glob([
        "thrift-12/*.h",
        "thrift-12/*.cpp",
    ]),
    includes = ["thrift-12"],
    linkopts = [
        "-lz",
        "-ldl",
        "-lbz2",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@apache_thrift//:thrift",
        "@cityhash",
        "@cpp3rd_lib//boost_1.67.0:boost",
        "@eigen_archive//:eigen3",
    ],
)

cc_binary(
    name = "server",
    srcs = glob(
        [
            "thrift-12/*.cpp",
            "thrift-12/*.h",
            "src/*.cpp",
            "include/*.h",
            "include/*.hpp",
            "gProxy/*.h",
            "gProxy/*.cpp",
        ],
    ),
    copts = [
        "-Ipsthrift/include",
        "-Ipsthrift/thrift-12",
    ],
    defines = ["HAVE_NETINET_IN_H"],
    linkopts = [
        "-lz",
        "-ldl",
        "-lbz2",
        "-llz4",
    ],
    deps = [
        "@apache_thrift//:thrift",
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@cpp3rd_lib//boost_1.67.0:boost",
        "@cpp3rd_lib//util",
        "@cpp3rd_lib//zk_client",
        "@eigen_archive//:eigen3",
        "@nlohmann_json//:json",
    ],
)

cc_binary(
    name = "client",
    srcs = glob(
        [
            "thrift/*.cpp",
            "thrift/*.h",
            "client/client.cpp",
            "include/*.h",
            "include/*.hpp",
            "src/*.cpp",
        ],
        exclude = ["src/main.cpp"],
    ),
    copts = [
        "-Ipsthrift/include",
        "-Ipsthrift/thrift",
    ],
    linkopts = [
        "-lz",
        "-ldl",
        "-lbz2",
        "-llz4",
    ],
    deps = [
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@cpp3rd_lib//boost_1.67.0:boost",
        "@cpp3rd_lib//eigen",
        "@cpp3rd_lib//json",
        "@cpp3rd_lib//thrift",
        "@cpp3rd_lib//zk_client",
    ],
)

cc_binary(
    name = "test",
    srcs = glob([
        "thrift/MatrixRand.h",
        "thrift/MatrixRand.cpp",
        "client/check_mencpy.cpp",
    ]),
    copts = ["-Ipsthrift/thrift"],
    deps = [
        "@cityhash",
        "@com_github_facebook_rocksdb//:rocksdb",
        "@cpp3rd_lib//boost_1.67.0:boost",
        "@cpp3rd_lib//eigen",
        "@cpp3rd_lib//json",
        "@cpp3rd_lib//thrift",
    ],
)
