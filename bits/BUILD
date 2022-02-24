package(default_visibility = ["//visibility:public"])

_COPTS = [
    "-std=gnu++2a",
]

cc_library(
    name = "stdcxx",
    hdrs = [
        "stdc++.h",
    ],
    copts = _COPTS,
    deps = [
        "@com_github_google_glog//:glog",
    ],
)
