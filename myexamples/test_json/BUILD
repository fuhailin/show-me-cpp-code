load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-json",
    srcs = ["hello-world.cc"],
    data = ["test.json"],
    deps = [
        "@nlohmann_json_lib//:nlohmann_json",
    ],
)

cc_binary(
    name = "test1",
    srcs = ["test1.cc"],
    deps = [
        "@nlohmann_json_lib//:nlohmann_json",
    ],
)
