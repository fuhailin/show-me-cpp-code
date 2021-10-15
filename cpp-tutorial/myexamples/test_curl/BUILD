cc_binary(
    name = "test_curl",
    srcs = [
        "curl_test.cc",
    ],
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    deps = [
        "@com_github_curl//:libcurl_openssl",
    ],
)
