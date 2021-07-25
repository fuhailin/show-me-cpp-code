cc_library(
    name = "tcmcp",
    srcs = glob([
        "thrift/GalaxyPredictorThrift/*.h",
        "thrift/GalaxyPredictorThrift/*.cpp",
        "include/*.h",
        "src/*.cpp",
        "thrift/psProxyThrift/*.cpp",
        "thrift/psProxyThrift/*.h",
        "thrift/HulkProxyThrift/*.h",
        "thrift/HulkProxyThrift/*.cpp",
    ]),
    includes = [
        "include",
        "thrift/GalaxyPredictorThrift",
        "thrift/HulkProxyThrift",
        "thrift/psProxyThrift",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:boost",
        "@nlohmann_json//:json",
        "@apache_thrift//:thrift",
        "//util",
        "//zk_client",
    ],
)

cc_library(
    name = "tcmcp_tf",
    srcs = glob([
        "thrift/GalaxyPredictorThrift/*.h",
        "thrift/GalaxyPredictorThrift/*.cpp",
        "include/*.h",
        "src/*.cpp",
        "thrift/psProxyThrift/*.cpp",
        "thrift/psProxyThrift/*.h",
        "thrift/HulkProxyThrift/*.h",
        "thrift/HulkProxyThrift/*.cpp",
    ]),
    includes = [
        "include",
        "thrift/GalaxyPredictorThrift",
        "thrift/HulkProxyThrift",
        "thrift/psProxyThrift",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:boost",
        "@nlohmann_json//:json",
        "@apache_thrift//:thrift",
        "//zk_client",
        "@tensorflow//util:util_tf",
    ],
)
