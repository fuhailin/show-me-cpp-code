# package(
#     default_visibility = [
#         "//parameter_server:internal",
#     ],
#     features = ["-layering_check"],
# )
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "get_host_ipaddress",
    srcs = ["get_host_ipaddress.cpp"],
    hdrs = ["get_host_ipaddress.h"],
)

cc_library(
    name = "ps_util",
    srcs = ["ps_util.cpp"],
    hdrs = ["ps_util.h"],
    deps = [
        "@cityhash",
        "@eigen_archive//:eigen3",
    ],
)

cc_library(
    name = "RWLock",
    srcs = ["RWLock.cpp"],
    hdrs = ["RWLock.h"],
)

cc_library(
    name = "time_function",
    srcs = ["time_function.cpp"],
    hdrs = ["time_function.h"],
)

cc_library(
    name = "util",
    hdrs = ["cache.h"],
    deps = [
        ":RWLock",
        ":get_host_ipaddress",
        ":ps_util",
        ":time_function",
    ],
)
