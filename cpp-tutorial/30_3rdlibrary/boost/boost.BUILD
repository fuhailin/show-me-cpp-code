licenses(["notice"])  # Boost software license

# Modified from https://github.com/tensorflow/tensorflow/blob/master/boost.BUILD
# and https://github.com/mzhaom/trunk/blob/master/third_party/boost/BUILD

cc_library(
    name = "boost",
    hdrs = glob([
        "boost/**/*.hpp",
        "boost/**/*.h",
        "boost/**/*.ipp",
    ]),
    includes = ["."],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "context",
    srcs = [
        "libs/context/src/asm/jump_x86_64_sysv_elf_gas.S",
        "libs/context/src/asm/make_x86_64_sysv_elf_gas.S",
        "libs/context/src/execution_context.cpp",
    ],
    copts = [
        "-DBOOST_USE_SEGMENTED_STACKS",
        "-fsplit-stack",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
    ],
)

cc_library(
    name = "filesystem",
    srcs = glob([
        "libs/filesystem/src/*.cpp",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
        ":system",
    ],
)

cc_library(
    name = "iostreams",
    srcs = [
        # intentionally left out other sources such as bzip2.cpp, add them back when we got the dependencies in
        "libs/iostreams/src/zlib.cpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
        "@zlib//:zlib",
    ],
)

cc_library(
    name = "program_options",
    srcs = glob([
        "libs/program_options/src/*.cpp",
        "libs/program_options/src/*.hpp",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
    ],
)

cc_library(
    name = "regex",
    srcs = glob([
        "libs/regex/src/*.cpp",
        "libs/regex/src/*.hpp",
    ]),
    copts = [
        "-DBOOST_FALLTHROUGH",
        "-Wno-unused-value",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
    ],
)

cc_library(
    name = "system",
    srcs = glob([
        "libs/system/src/*.cpp",
    ]),
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
    ],
)
