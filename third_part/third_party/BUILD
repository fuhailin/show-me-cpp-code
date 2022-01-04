load("@bazel_skylib//rules:build_test.bzl", "build_test")
load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "test",
    deps = [
        "@com_github_grpc_grpc//:grpc",
        "@com_github_grpc_grpc//:grpc++",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
        "@cpp3rd_lib//zookeeper",
        "@flatbuffers",
    ],
)

build_test(
    name = "build_test",
    targets = [
        "@com_github_facebook_rocksdb//:rocksdb",
        "@rapidjson//:rapidjson",
        "@libevent//:libevent",
        "@com_google_absl//absl/strings",
        "@apache_thrift//:thrift",
        "@cppunit//:cppunit",
        "@cpp3rd_lib//zookeeper:zookeeper",
        "@cpp3rd_lib//tensorflow:tensorflow_cc",
        "@cpp3rd_lib//tensorflow:tensorflow_framework",
        "@com_github_grpc_grpc//:grpc",
        "@com_github_grpc_grpc//:grpc++",
        # "@openssl//:openssl",
        # "@zeromq//:libzmq",
        # "@com_github_jupp0r_prometheus_cpp//pull",
        # "@com_google_protobuf//:protobuf_lite",
        # "@com_google_protobuf//:protobuf",
        # "@com_google_protobuf//:protoc_lib",
        # "@com_google_protobuf//:protoc",
        # "@com_google_absl//absl/strings",
        # "@com_google_absl//absl/types:span",
        # "@llvm-project//llvm:Support",
        # "@llvm-project//mlir:IR",
        # "@llvm-project//mlir:Pass",
        # "@llvm-project//mlir:Support",
        # "@llvm-project//mlir:Transforms",
        # "@flatbuffers",
        # "@snappy",
        # "@curl",
        # "@boringssl//:crypto",
        # "@jsoncpp_git//:jsoncpp",
        # "@com_googlesource_code_re2//:re2",
        # "@farmhash_archive//:farmhash",
        # "@fft2d",
        # "@highwayhash//:sip_hash",
        # "@zlib",
        # "@gif",
        # "@six_archive//:six",
        # "@pybind11",
        # "@eigen_archive//:eigen3",
        # "@eigen_archive//:eigen_header_files",
        # "@com_github_gflags_gflags//:gflags",
        # "@com_github_google_glog//:glog",
        # "@com_github_google_double_conversion//:double-conversion",
        # "@lz4",
        # "@org_lzma_lzma//:lzma",
        # "@zstd//:zstd",
        # "@ps-lite//:ps-lite",
        # "@rules_compressor//example:zlib_usage_example",
        # "@boost",
        # "@librdkafka//:kafka",
    ],
)

compilation_database(
    name = "example_compdb",
    # OUTPUT_BASE is a dynamic value that will vary for each user workspace.
    # If you would like your build outputs to be the same across users, then
    # skip supplying this value, and substitute the default constant value
    # "__OUTPUT_BASE__" through an external tool like `sed` or `jq` (see
    # below shell commands for usage).
    output_base = OUTPUT_BASE,
    targets = [
        "@flatbuffers",
    ],
)
