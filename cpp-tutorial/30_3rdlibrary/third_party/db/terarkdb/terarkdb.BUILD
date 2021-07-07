load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

make(
    name = "rocksdb",
    lib_source = "@com_github_facebook_rocksdb//:all",
    linkopts = ["-ldl"],
    make_commands = [
        # Solution for https://github.com/bazelbuild/rules_foreign_cc/issues/239
        # "export CFLAGS=$(echo $CFLAGS | sed 's/-D__DATE__=.redacted.//')",
        # "export CXXFLAGS=$(echo $CXXFLAGS | sed 's/-D__DATE__=.redacted.//')",
        # "export ASFLAGS=$(echo $ASFLAGS | sed 's/-D__DATE__=.redacted.//')",
        # Hack - rocksdb uses CFLAGS, related PR https://github.com/facebook/rocksdb/pull/6465
        # "export CFLAGS=\"$CFLAGS $CPPFLAGS -DSNAPPY\"",
        "make -j `nproc` static_lib",
        # Hack - for some reason libs and headers are not included
        "cp librocksdb.a $$INSTALLDIR$$/lib/librocksdb.a",
        "cp -RL include $$INSTALLDIR$$",
    ],
    make_env_vars = {
        "ROCKSDB_DISABLE_ZLIB": "1",
        "ROCKSDB_DISABLE_BZIP": "1",
        # Solution for https://github.com/bazelbuild/rules_foreign_cc/issues/185
        "AR": "/usr/bin/ar",
    },
    static_libraries = ["librocksdb.a"],
    deps = [
        # "@com_github_gflags_gflags//:gflags",
        "@bzip2",
        # "@com_google_googletest//:gtest",
        # "@lz4",
        "@snappy",
        "@zlib",
        # "@zstd",
    ],
)

# make(
#     name = "librocksdb",
#     lib_source = "@rocksdb//:all",  # mandatory
#     make_commands = [
#         " ".join([
#             # "INSTALL_PATH=${INSTALLDIR}", # v6.0.1
#             "make",
#             # "install", ## both static and shared
#             "install-shared",
#             "-j2",
#         ]) + " " + ENV_VARS,
#         " ".join([
#             # "INSTALL_PATH=${INSTALLDIR}", # v6.0.1
#             "make",
#             "install-static",
#             "-j2",
#         ]) + " " + ENV_VARS,
#     ],
#     make_env_vars = {
#         "PREFIX": "${INSTALLDIR}",
#         "VERBOSE": "1",
#     },
#     out_lib_dir = "lib",
#     prefix = "${INSTALLDIR}",
#     shared_libraries = select(
#         {
#             "//bzl/host:macos": [
#                 "librocksdb.dylib",
#                 "librocksdb.{major}.dylib".format(
#                     major = VERSION_MAJOR,
#                 ),
#                 "librocksdb.{major}.{minor}.dylib".format(
#                     major = VERSION_MAJOR,
#                     minor = VERSION_MINOR,
#                 ),
#                 "librocksdb.{major}.{minor}.{patch}.dylib".format(
#                     major = VERSION_MAJOR,
#                     minor = VERSION_MINOR,
#                     patch = VERSION_PATCH,
#                 ),
#             ],
#             "//bzl/host:linux": [
#                 "librocksdb.so",
#                 "librocksdb.so.{major}".format(
#                     major = VERSION_MAJOR,
#                 ),
#                 "librocksdb.so.{major}.{minor}".format(
#                     major = VERSION_MAJOR,
#                     minor = VERSION_MINOR,
#                 ),
#                 "librocksdb.so.{major}.{minor}.{patch}".format(
#                     major = VERSION_MAJOR,
#                     minor = VERSION_MINOR,
#                     patch = VERSION_PATCH,
#                 ),
#             ],
#         },
#         no_match_error = "Unsupported platform. MacOS or Linux only.",
#     ),
#     static_libraries = ["librocksdb.a"],
#     visibility = ["//visibility:public"],
# )
