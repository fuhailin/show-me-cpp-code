cc_binary(
    name = "main",
    srcs = ["thread_test.cc"],
    copts = [
        "-std=c++11",
    ],
    linkopts = ["-lpthread"],
)



cc_binary(
    name = "thread1",
    srcs = ["thread_test1.cc"],
)

cc_binary(
    name = "thread_pool_test",
    srcs = ["thread_pool_test.cc"],
    deps = [
        # "@boost",
        "@boost//:asio",
        "@boost//:thread",
    ],
    # copts = [
    #     "-std=c++14",
    # ],
)
