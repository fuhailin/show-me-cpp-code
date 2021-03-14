licenses(["notice"])

config_setting(
    name = "linux",
    values = {"cpu": "linux"},
)

config_setting(
    name = "macos",
    values = {"cpu": "darwin"},
)

_COMMON_COPTS = [
    "-std=c++11",
    "-fno-omit-frame-pointer",
    "-fno-builtin-memcmp",
    "-momit-leaf-frame-pointer",
    "-msse3",
    "-msse4",
    "-msse4.1",
    "-msse4.2",
    "-mpclmul",
    "-Werror",
    "-Wsign-compare",
    "-Wshadow",
    "-Wno-unused-parameter",
    "-Wno-unused-variable",
    "-Woverloaded-virtual",
    "-Wnon-virtual-dtor",
    "-Wno-missing-field-initializers",
]

genrule(
    name = "build_version",
    srcs = glob([".git/**/*"]) + [
        "util/build_version.cc.in",
    ],
    outs = [
        "util/build_version.cc",
    ],
    cmd = "cat external/com_github_facebook_rocksdb/util/build_version.cc.in >> $(@)",
)

cc_library(
    name = "rocksdb",
    srcs = glob([
        "**/*.h",
    ]) + glob(
        [
            "cache/**/*.cc",
            "db/**/*.cc",
            "env/**/*.cc",
            "memtable/**/*.cc",
            "monitoring/**/*.cc",
            "options/**/*.cc",
            "port/**/*.cc",
            "table/**/*.cc",
            "tools/**/*.cc",
            "util/**/*.cc",
            "utilities/**/*.cc",
        ],
        exclude = [
            "**/*_bench.cc",
            "**/*_test.cc",
            "**/*_test2.cc",
            "**/win/**/*.cc",
            "tools/rdb/*",
            "utilities/env_librados.cc",
            "**/*_stress.cc",
            "tools/dump/rocksdb_dump.cc",
            "tools/sst_dump.cc",
            "tools/ldb.cc",
            "tools/dump/rocksdb_undump.cc",
            "utilities/column_aware_encoding_exp.cc",
            "utilities/persistent_cache/hash_table_bench.cc",
        ],
    ) + [
        ":build_version",
    ],
    hdrs = glob([
        "include/rocksdb/**/*.h",
    ]),
    copts = [
        "-DROCKSDB_PLATFORM_POSIX",
        "-DROCKSDB_LIB_IO_POSIX",
        "-DROCKSDB_SUPPORT_THREAD_LOCAL",
        "-DGFLAGS=1",
        "-std=c++11",
    ] + select({
        ":macos": [
            "-DOS_MACOSX",
        ],
        ":linux": [
            "-DOS_LINUX",
        ],
        "//conditions:default": [
            "-DOS_LINUX",
        ],
    }),
    # copts = [
    #     "-fno-omit-frame-pointer",
    #     "-momit-leaf-frame-pointer",
    #     "-msse",
    #     "-msse4.2",
    #     "-pthread",
    #     "-Werror",
    #     "-Wsign-compare",
    #     "-Wshadow",
    #     "-Wno-unused-parameter",
    #     "-Wno-unused-variable",
    #     "-Woverloaded-virtual",
    #     "-Wnon-virtual-dtor",
    #     "-Wno-missing-field-initializers",
    #     "-fno-builtin-memcmp",
    #     "-std=c++11",
    #     "-mpclmul",
    #     "-O2",
    # ],
    # defines = [
    #     "ROCKSDB_FALLOCATE_PRESENT",
    #     "ROCKSDB_LIB_IO_POSIX",
    #     "ROCKSDB_MALLOC_USABLE_SIZE",
    #     "ROCKSDB_PLATFORM_POSIX",
    #     "ROCKSDB_SUPPORT_THREAD_LOCAL",
    #     "GFLAGS=gflags",
    #     "OS_LINUX",
    #     "SNAPPY",
    #     "HAVE_SSE42",
    #     "ZLIB",
    #     "LZ4",
    #     "ZSTD",
    #     "ROCKSDB_SCHED_GETCPU_PRESENT",
    #     "ROCKSDB_MALLOC_USABLE_SIZE",
    # ],
    includes = [
        ".",
        "include",
        "util",
    ],
    linkopts = [
        "-lm",
        "-lpthread",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        # "@com_github_google_glog//:glog",
        "@com_google_googletest//:gtest",
        # "@lz4",
        # "@snappy",
        # "@zlib",
        # "@zstd",
    ],
)

filegroup(
    name = "private_hdrs",
    srcs = glob(
        ["**/*.h"],
        exclude = ["include/**/*.h"],
    ),
)

cc_library(
    name = "rocksdb_tools_lib",
    # srcs = glob([
    #     "test_util/*.cc",
    #     "test_util/*.h",
    #     "db/db_test_util.cc",

    # ])+ [
    #     ":private_hdrs",
    # ],
    srcs = [
        "db/db_test_util.cc",
        "table/mock_table.cc",
        "tools/block_cache_analyzer/block_cache_trace_analyzer.cc",
        "tools/trace_analyzer_tool.cc",
        "utilities/cassandra/test_utils.cc",
        ":private_hdrs",
    ],
    copts = _COMMON_COPTS,
    visibility = ["//visibility:public"],
    deps = [
        ":rocksdb",
    ],
)

cc_binary(
    name = "db_stress",
    srcs = glob([
        "db_stress_tool/*.cc",
        "db_stress_tool/*.h",
    ]),
    copts = _COMMON_COPTS,
    visibility = ["//visibility:public"],
    deps = [
        ":rocksdb",
    ],
)

[
    cc_binary(
        name = "%s" % f.replace("/", "_"),
        srcs = [
            "tools/%s.cc" % f,
            ":private_hdrs",
        ],
        copts = _COMMON_COPTS,
        deps = [
            ":rocksdb_tools_lib",
        ],
    )
    for f in [
        "sst_dump",
        "ldb",
        "db_sanity_test",
        "write_stress",
        "db_repl_stress",
        "dump/rocksdb_dump",
        "dump/rocksdb_undump",
    ]
]
