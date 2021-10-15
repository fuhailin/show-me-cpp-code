load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

_CACHE_ENTRIES = {
    "BUILD_EXAMPLES": "off",
    "BUILD_SHARED_LIBS": "off",
    "BUILD_TESTING": "off",
    "CMAKE_FIND_DEBUG_MODE": "on",
    "CMAKE_PREFIX_PATH": "${CMAKE_PREFIX_PATH:-};$EXT_BUILD_DEPS/openssl",
}

_LINUX_CACHE_ENTRIES = dict(_CACHE_ENTRIES.items() + {
    "CMAKE_C_FLAGS": "${CMAKE_C_FLAGS:-} -fPIC",
}.items())

cmake(
    name = "libssh2",
    build_args = [
        "-j `nproc`",
    ],
    cache_entries = select({
        "@platforms//os:linux": _LINUX_CACHE_ENTRIES,
        "//conditions:default": _CACHE_ENTRIES,
    }),
    lib_source = ":all_srcs",
    out_lib_dir = select({
        "@platforms//os:linux": "lib64",
        "//conditions:default": "lib",
    }),
    out_static_libs = select({
        # TODO: I'm guessing at this name. Needs to be checked on windows.
        "@platforms//os:windows": ["ssh2.lib"],
        "//conditions:default": ["libssh2.a"],
    }),
    visibility = ["//visibility:public"],
    deps = ["@openssl"],
)
