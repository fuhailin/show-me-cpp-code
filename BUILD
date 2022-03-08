load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "build_test_mac",
    deps = [
        # "@boost",
        "@cityhash",
        "@com_github_facebook_zstd//:zstd",
        "@com_github_fmtlib_fmt//:fmt",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_double_conversion//:double-conversion",
        "@com_github_google_flatbuffers//:flatbuffers",
        "@com_github_google_glog//:glog",
        "@com_github_google_snappy//:snappy",
        "@com_github_grpc_grpc//:grpc",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_tencent_rapidjson//:rapidjson",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest",
        "@com_google_protobuf//:protobuf",
        "@com_google_protobuf//:protobuf_lite",
        "@com_google_protobuf//:protoc",
        "@com_google_protobuf//:protoc_lib",
        "@eigen",
        "@libevent",
        "@lz4",
        "@nlohmann_json_lib//:nlohmann_json",
        "@openblas",
        "@org_bzip_bzip2//:bzip2",
        "@org_lzma_lzma//:lzma",
        "@pybind11",
        "@sparsehash_c11//:dense_hash_map",
        "@spdlog",
        "@uuid",
        "@zlib",
    ],
)

# "@cpp3rd_lib//tensorflow:tensorflow_cc",
# "@cpp3rd_lib//tensorflow:tensorflow_framework",
# "@cpp3rd_lib//zk_client",
# "@cpp3rd_lib//zookeeper",
# "@apache_thrift//:thrift",
# "@curl",
# "@oneDNN//:mkldnn",

build_test(
    name = "build_test",
    targets = [
        ":build_test_mac",
    ],
)

# Generates `compile_commands.json` for use with clangd.
#
# Run `bazel build //:refresh_compile_commands` to generate.
#
compilation_database(
    name = "refresh_compile_commands",
    # OUTPUT_BASE is a dynamic value that will vary for each user workspace.
    # If you would like your build outputs to be the same across users, then
    # skip supplying this value, and substitute the default constant value
    # "__OUTPUT_BASE__" through an external tool like `sed` or `jq` (see
    # below shell commands for usage).
    output_base = OUTPUT_BASE,
    targets = [
        "//src/benchmark:main_benchmark",
        "//src/main:main",
        "//myexamples/test_benchmark:benchmark1",
        "//myexamples/test_benchmark:benchmark2",
        "//myexamples/test_gtest:gmock_leak_test_",
        "//myexamples/test_logger:test_spdlog",
        "//myexamples/test_sparsehash:map",
        "//myexamples/test_snappy:example",
        "//myexamples/test_fmt:main",
        "//myexamples/test_eigen_city:test_city",
        "//myexamples/test_eigen_city:main",
        ":build_test_mac",
    ],
)
