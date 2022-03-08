load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main_benchmark",
    srcs = ["main_benchmark.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "main_benchmark_adder",
    srcs = ["main_benchmark_adder.cc"],
    deps = [
        "//src/lib/search:SearchLib",
        "@com_google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "main_benchmark_sort",
    srcs = ["main_benchmark_sort.cc"],
    deps = [
        "//src/lib/sort:SortLib",
        "@com_google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "main_benchmark_search",
    srcs = ["main_benchmark_search.cc"],
    deps = [
        "//src/lib/search:SearchLib",
        "@com_google_benchmark//:benchmark",
    ],
)
