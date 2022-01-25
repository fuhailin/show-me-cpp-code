cc_library(
    name = "GalaxyPredictorThrift",
    srcs = [
        "thrift/GalaxyPredictorThrift/GalaxyPredict.cpp",
        "thrift/GalaxyPredictorThrift/galaxy_predict_constants.cpp",
        "thrift/GalaxyPredictorThrift/galaxy_predict_types.cpp",
    ],
    hdrs = [
        "thrift/GalaxyPredictorThrift/GalaxyPredict.h",
        "thrift/GalaxyPredictorThrift/galaxy_predict_constants.h",
        "thrift/GalaxyPredictorThrift/galaxy_predict_types.h",
    ],
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_library(
    name = "HulkProxyThrift",
    srcs = [
        "thrift/HulkProxyThrift/HulkProxyServ.cpp",
        "thrift/HulkProxyThrift/hulk_proxy_constants.cpp",
        "thrift/HulkProxyThrift/hulk_proxy_types.cpp",
        "thrift/HulkProxyThrift/scan_data_constants.cpp",
        "thrift/HulkProxyThrift/scan_data_types.cpp",
    ],
    hdrs = [
        "thrift/HulkProxyThrift/HulkProxyServ.h",
        "thrift/HulkProxyThrift/hulk_proxy_constants.h",
        "thrift/HulkProxyThrift/hulk_proxy_types.h",
        "thrift/HulkProxyThrift/scan_data_constants.h",
        "thrift/HulkProxyThrift/scan_data_types.h",
    ],
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_library(
    name = "psProxyThrift",
    srcs = [
        "thrift/psProxyThrift/psProxyServ.cpp",
        "thrift/psProxyThrift/ps_proxy_thrift_constants.cpp",
        "thrift/psProxyThrift/ps_proxy_thrift_types.cpp",
    ],
    hdrs = [
        "thrift/psProxyThrift/psProxyServ.h",
        "thrift/psProxyThrift/ps_proxy_thrift_constants.h",
        "thrift/psProxyThrift/ps_proxy_thrift_types.h",
    ],
    deps = [
        "@apache_thrift//:thrift",
    ],
)

cc_library(
    name = "tcmcp",
    srcs = [
        "tcmcp_GalaxyPredict.cpp",
        "tcmcp_HulkProxyServ.cpp",
        "tcmcp_psProxyServ.cpp",
    ],
    hdrs = [
        "ThriftClientMultiConnectPlug.h",
        "tcmcp_GalaxyPredict.h",
        "tcmcp_HulkProxyServ.h",
        "tcmcp_psProxyServ.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":GalaxyPredictorThrift",
        ":HulkProxyThrift",
        ":psProxyThrift",
        "//parameter_server/util:RWLock",
        "@cpp3rd_lib//zk_client",
        "@nlohmann_json//:json",
    ],
)
