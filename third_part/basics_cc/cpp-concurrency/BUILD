cc_binary(
    name = "00",
    srcs = ["00_hello_thread.cpp"],
)

cc_binary(
    name = "000",
    srcs = ["000_hello_thread.cpp"],
)

cc_binary(
    name = "001",
    srcs = ["001_thread_print.cc"],
)

cc_binary(
    name = "002",
    srcs = ["002_thread_print.cc"],
)

cc_binary(
    name = "01",
    srcs = ["01_lambda_thread.cpp"],
)

cc_binary(
    name = "02",
    srcs = ["02_thread.cpp"],
    copts = [
        "-std=c++11",
    ],
    linkopts = ["-lpthread"],
)

cc_binary(
    name = "semaphore",
    srcs = ["semaphore_test.cc"],
    deps = [
        "@boost//:boost",
        "@com_github_google_glog//:glog",
    ],
)
