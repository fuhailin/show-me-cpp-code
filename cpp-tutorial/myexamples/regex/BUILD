cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-std=c++11",
    ],
)

cc_binary(
    name = "main1",
    srcs = ["main1.cc"],
    copts = [
        "-std=c++11",
    ],
    deps = [
        "@boost//:regex",
        # "@boost//:lexical_cast",
    ],
)
