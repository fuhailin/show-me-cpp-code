genrule(
    name = "generate_format_tables",
    srcs = [
        "folly/build/generate_format_tables.py",
    ],
    outs = [
        "FormatTables.cpp",
    ],
    cmd = "$(location folly/build/generate_format_tables.py) --install_dir=$(GENDIR)/third_party/folly",
)

genrule(
    name = "generate_escape_tables",
    srcs = [
        "folly/build/generate_escape_tables.py",
    ],
    outs = [
        "EscapeTables.cpp",
    ],
    cmd = "$(location folly/build/generate_escape_tables.py) --install_dir=$(GENDIR)/third_party/folly",
)

genrule(
    name = "generate_varint_tables",
    srcs = [
        "folly/build/generate_varint_tables.py",
    ],
    outs = [
        "GroupVarintTables.cpp",
    ],
    cmd = "$(location folly/build/generate_varint_tables.py) --install_dir=$(GENDIR)/third_party/folly",
)

cc_binary(
    name = "GenerateFingerprintTables",
    srcs = [
        "folly/build/GenerateFingerprintTables.cpp",
        "folly/detail/FingerprintPolynomial.h",
    ],
    deps = [
        ":base",
        "@com_github_gflags_gflags//:gflags",
    ],
)

genrule(
    name = "generate_fingerprint_tables",
    srcs = [
        ":GenerateFingerprintTables",
    ],
    outs = [
        "FingerprintTables.cpp",
    ],
    cmd = "$(location :GenerateFingerprintTables) --install_dir=$(GENDIR)/third_party/folly",
)

genrule(
    name = "folly_config",
    outs = ["folly/folly-config.h"],
    cmd = "\n".join([
        "cat << 'EOF' >$@",
        "#pragma once",
        "#if !defined(FOLLY_MOBILE)",
        "#if defined(__ANDROID__) || \\",
        "    (defined(__APPLE__) &&  \\",
        "     (TARGET_IPHONE_SIMULATOR || TARGET_OS_SIMULATOR || TARGET_OS_IPHONE))",
        "#define FOLLY_MOBILE 1",
        "#else",
        "#define FOLLY_MOBILE 0",
        "#endif",
        "#endif // FOLLY_MOBILE",
        "#define FOLLY_HAVE_PTHREAD 1",
        "#define FOLLY_HAVE_PTHREAD_ATFORK 1",
        "#define FOLLY_HAVE_LIBGFLAGS 1",
        "#define FOLLY_UNUSUAL_GFLAGS_NAMESPACE 0",
        "#define FOLLY_GFLAGS_NAMESPACE google",
        "#define FOLLY_HAVE_LIBGLOG 1",
        "#define FOLLY_HAVE_MALLOC_H 1",
        "#define FOLLY_HAVE_BITS_CXXCONFIG_H 1",
        "#define FOLLY_HAVE_FEATURES_H 1",
        "#if FOLLY_HAVE_FEATURES_H",
        "#include <features.h>",
        "#endif",
        "#define FOLLY_HAVE_MEMRCHR 1",
        "#define FOLLY_HAVE_PREADV 1",
        "#define FOLLY_HAVE_PWRITEV 1",
        "#define FOLLY_HAVE_CLOCK_GETTIME 1",
        "#define FOLLY_HAVE_OPENSSL_ASN1_TIME_DIFF 1",
        "#define FOLLY_HAVE_IFUNC 1",
        "#define FOLLY_HAVE_STD__IS_TRIVIALLY_COPYABLE 1",
        "#define FOLLY_HAVE_UNALIGNED_ACCESS 1",
        "#define FOLLY_HAVE_VLA 1",
        "#define FOLLY_HAVE_WEAK_SYMBOLS 1",
        "#define FOLLY_HAVE_LINUX_VDSO 1",
        "#define FOLLY_HAVE_MALLOC_USABLE_SIZE 1",
        "#define FOLLY_HAVE_INT128_T 1",
        "#define FOLLY_HAVE_WCHAR_SUPPORT 1",
        "#define FOLLY_HAVE_EXTRANDOM_SFMT19937 1",
        "#define HAVE_VSNPRINTF_ERRORS 1",
        "#define FOLLY_USE_SYMBOLIZER 1",
        "#define FOLLY_DEMANGLE_MAX_SYMBOL_SIZE 1024",
        "#define FOLLY_HAVE_SHADOW_LOCAL_WARNINGS 1",
        "#define FOLLY_HAVE_LIBLZ4 1",
        "#define FOLLY_HAVE_LIBSNAPPY 1",
        "#define FOLLY_HAVE_LIBZ 1",
        "#define FOLLY_HAVE_LIBZSTD 1",
        "#define FOLLY_HAVE_LIBBZ2 1",
        "EOF",
    ]),
)

cc_library(
    name = "base",
    srcs = [
        "folly/Conv.cpp",
        "folly/Demangle.cpp",
        "folly/Format.cpp",
        "folly/SpookyHashV1.cpp",
        "folly/SpookyHashV2.cpp",
        "folly/String.cpp",
        "folly/StringBase.cpp",
        "folly/Unicode.cpp",
        "folly/detail/Malloc.h",
        "folly/detail/RangeCommon.h",
        "folly/detail/RangeSse42.h",
        "folly/detail/UncaughtExceptionCounter.h",
        ":generate_escape_tables",
        ":generate_format_tables",
    ],
    hdrs = [
        # "@cc_third_party//third_party/folly/folly-config.h",
        "folly/ApplyTuple.h",
        "folly/CPortability.h",
        "folly/Conv.h",
        "folly/CpuId.h",
        "folly/Demangle.h",
        "folly/Exception.h",
        "folly/ExceptionWrapper.h",
        "folly/FBString.h",
        "folly/FBVector.h",
        "folly/Fingerprint.h",
        "folly/Format.h",
        "folly/Format-inl.h",
        "folly/FormatArg.h",
        "folly/FormatTraits.h",
        "folly/Hash.h",
        "folly/Likely.h",
        "folly/Malloc.h",
        "folly/MoveWrapper.h",
        "folly/Portability.h",
        "folly/Preprocessor.h",
        "folly/ProducerConsumerQueue.h",
        "folly/Range.h",
        "folly/ScopeGuard.h",
        "folly/SpookyHashV1.h",
        "folly/SpookyHashV2.h",
        "folly/String.h",
        "folly/String-inl.h",
        "folly/ThreadName.h",
        "folly/Traits.h",
        "folly/Unicode.h",
        "folly/detail/ExceptionWrapper.h",
        "folly/experimental/io/FsUtil.h",
        "folly/portability/Syscall.h",
    ] + [
        ":folly_config",
    ],
    includes = [
        "linux-k8",
        "upstream",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:config",
        "@boost//:conversion",
        "@boost//:iterator",
        "@boost//:regex",
        "@boost//:type_traits",
        "@boost//:utility",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@double-conversion//:double-conversion",
    ],
)

cc_library(
    name = "FingerprintTables",
    srcs = [
        ":generate_fingerprint_tables",
    ],
    hdrs = [
        "folly/detail/FingerprintPolynomial.h",
    ],
    deps = [
        ":base",
    ],
)

# cc_library(
#   name = "checksum",
#   visibility = ["//visibility:public"],
#   hdrs = [
#     "folly/Checksum.h"
#   ],
#   srcs = [
#     "folly/Checksum.cpp",
#   ],
#   deps = [
#     ":base",
#     "@boost//:crc",
#   ],
# )

cc_library(
    name = "folly",
    srcs = glob([
        "folly/detail/*.h",
    ]) + [
        ":generate_varint_tables",
        "folly/Bits.cpp",
        "folly/File.cpp",
        "folly/FileUtil.cpp",
        "folly/GroupVarint.cpp",
        "folly/IPAddress.cpp",
        "folly/IPAddressV4.cpp",
        "folly/IPAddressV6.cpp",
        "folly/LifoSem.cpp",
        "folly/detail/CacheLocality.cpp",
        "folly/detail/Futex.cpp",
        "folly/dynamic.cpp",
        "folly/io/Compression.cpp",
        "folly/io/IOBuf.cpp",
        "folly/io/IOBufQueue.cpp",
        "folly/io/ShutdownSocketSet.cpp",
        "folly/SharedMutex.cpp",
        "folly/detail/ThreadLocalDetail.cpp",
        # These require libevent
        "folly/MacAddress.cpp",
        "folly/Random.cpp",
        "folly/SafeAssert.cpp",
        "folly/Singleton.cpp",
        "folly/SocketAddress.cpp",
        "folly/Subprocess.cpp",
        "folly/ThreadCachedArena.cpp",
        "folly/TimeoutQueue.cpp",
        "folly/Uri.cpp",
        "folly/detail/MemoryIdler.cpp",
        "folly/json.cpp",
        "folly/stats/Instantiations.cpp",
    ],
    hdrs = glob([
        "folly/stats/*.h",
        "folly/gen/*.h",
        "folly/*.h",
        "folly/detail/*.h",
    ]) + [
        "folly/experimental/ReadMostlySharedPtr.h",
        "folly/experimental/TLRefCount.h",
        "folly/io/Compression.h",
        "folly/io/Cursor.h",
        "folly/io/IOBuf.h",
        "folly/io/IOBufQueue.h",
        "folly/io/ShutdownSocketSet.h",
        "folly/io/async/Request.h",
    ],
    copts = [
        "-pthread",
    ],
    linkopts = [
        "-ldl",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":base",
        "@double-conversion//:double-conversion",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
        # "//third_party/libevent:libevent",
        "@boost//:algorithm",  # For boost/non_copyable
        "@boost//:core",  # For boost/non_copyable
        "@boost//:container",
        "@boost//:intrusive",
        "@boost//:iterator",
        "@boost//:multi_index",
        "@boost//:regex",
        "@boost//:thread",
        "@boost//:utility",  # For boost/operators.hpp
    ],
)

cc_library(
    name = "async",
    srcs = [
        "folly/io/async/AsyncServerSocket.cpp",
        "folly/io/async/AsyncSignalHandler.cpp",
        "folly/io/async/AsyncSocket.cpp",
        "folly/io/async/AsyncTimeout.cpp",
        "folly/io/async/AsyncUDPSocket.cpp",
        "folly/io/async/EventBase.cpp",
        "folly/io/async/EventBaseManager.cpp",
        "folly/io/async/EventHandler.cpp",
        "folly/io/async/HHWheelTimer.cpp",
    ],
    hdrs = glob([
        "folly/io/async/*.h",
    ]) + [
        "folly/experimental/ExecutionObserver.h",
        "folly/futures/DrivableExecutor.h",
    ],
    defines = [
        "FOLLY_HAVE_VLA=0",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":folly",
        "//external:libssl",
        "//third_party/libevent",
        "@boost//:iterator",
    ],
)

cc_library(
    name = "futures",
    srcs = glob([
        "folly/futures/*.cpp",
        "folly/futures/detail/*.cpp",
        "folly/experimental/fibers/*.cpp",
    ]),
    hdrs = glob([
        "folly/futures/*.h",
        "folly/futures/detail/*.h",
        "folly/experimental/fibers/*.h",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        ":async",
        ":folly",
        "@boost//:context",
    ],
)

cc_library(
    name = "ssl",
    srcs = [
        "folly/io/async/AsyncSSLSocket.cpp",
        "folly/io/async/SSLContext.cpp",
    ],
    hdrs = [
        "folly/io/async/AsyncSSLSocket.h",
        "folly/io/async/SSLContext.h",
    ],
    defines = [
        "FOLLY_HAVE_VLA=0",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":async",
        "//external:libssl",
    ],
)

# Broken because missing dwarf.h
#
# cc_library(
#   name = "symbolizer",
#   visibility = ["//visibility:public"],
#   hdrs = glob([
#     "folly/experimental/symbolizer/*.h",
#   ]),
#   srcs = glob([
#     "folly/experimental/symbolizer/*.cpp",
#   ]),
#   copts = [
#     #'-DHAVE_LINK_H=1'
#   ],
#   deps = [
#     ":base",
#     ":folly",
#     "@boost//:assert",
#     "@boost//:container",
#     "@boost//:functional",
#     "@boost//:iterator",
#     "@boost//:intrusive",
#     "@boost//:throw_exception",
#     "@boost//:type_index",
#     "@boost//:variant",
#   ],
# )

cc_library(
    name = "recordio",
    srcs = [
        "folly/MemoryMapping.cpp",
        "folly/experimental/io/FsUtil.cpp",
        "folly/experimental/io/HugePages.cpp",
        "folly/io/RecordIO.cpp",
    ],
    hdrs = [
        "folly/MemoryMapping.h",
        "folly/experimental/io/FsUtil.h",
        "folly/experimental/io/HugePages.h",
        "folly/io/RecordIO.h",
        "folly/io/RecordIO-inl.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":folly",
        "@boost//:filesystem",
    ],
)

# Test libraries and tests.
cc_library(
    name = "testutil",
    testonly = 1,
    srcs = [
        "folly/experimental/TestUtil.cpp",
    ],
    hdrs = [
        "folly/experimental/TestUtil.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":base",
        ":folly",
        "@boost//:filesystem",
        "@boost//:regex",
    ],
)

cc_library(
    name = "benchmark",
    testonly = 1,
    srcs = [
        "folly/Benchmark.cpp",
    ],
    hdrs = [
        "folly/Benchmark.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":folly",
        "@boost//:function_types",
        "@boost//:regex",
    ],
)

cc_test(
    name = "AsciiCaseInsensitiveTest",
    srcs = [
        "folly/test/AsciiCaseInsensitiveTest.cpp",
    ],
    deps = [
        ":base",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest",
    ],
)

# cc_test(
#   name = "ChecksumTest",
#   srcs = [
#     "folly/test/ChecksumTest.cpp"
#   ],
#   deps = [
#     ":checksum",
#     ":benchmark",
#     "@com_github_gflags_gflags//:gflags",
#     "@com_google_googletest//:gtest",
#   ]
# )

cc_test(
    name = "ProducerConsumerQueueTest",
    srcs = [
        "folly/test/ProducerConsumerQueueTest.cpp",
    ],
    deps = [
        ":base",
        "@boost//:core",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "StringTest",
    srcs = [
        "folly/test/StringTest.cpp",
    ],
    deps = [
        ":base",
        ":benchmark",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "subprocess_test_parent_death_helper",
    testonly = 1,
    srcs = [
        "folly/test/SubprocessTestParentDeathHelper.cpp",
    ],
    deps = [
        ":folly",
        ":recordio",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_test(
    name = "SubprocessTest",
    srcs = [
        "folly/test/SubprocessTest.cpp",
    ],
    data = [
        ":subprocess_test_parent_death_helper",
    ],
    deps = [
        ":benchmark",
        ":folly",
        ":recordio",
        ":testutil",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "UriTest",
    srcs = [
        "folly/test/UriTest.cpp",
    ],
    deps = [
        ":benchmark",
        ":folly",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "VarintTest",
    srcs = [
        "folly/test/VarintTest.cpp",
    ],
    deps = [
        ":benchmark",
        ":folly",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_googletest//:gtest",
    ],
)
