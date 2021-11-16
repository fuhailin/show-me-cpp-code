cc_binary(
    name = "rdkafka_example",
    srcs = [
        "rdkafka_example.cpp",
    ],
    # copts = [
    #     "-std=c++14",
    # ],
    deps = [
        "@librdkafka//:kafka",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "kafka_consumer",
    srcs = [
        "kafka_consumer.c",
    ],
    deps = [
        "@librdkafka//:kafka",
    ],
)

cc_binary(
    name = "rdkafka_complex_consumer_example",
    srcs = [
        "rdkafka_complex_consumer_example.cpp",
    ],
    deps = [
        "@com_github_google_glog//:glog",
        "@librdkafka//:kafka",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        "@librdkafka//:kafka",
    ],
)
