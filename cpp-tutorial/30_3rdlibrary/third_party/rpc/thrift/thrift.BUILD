load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

configure_env_vars = select({
    ":macos": {
        "AR": "/usr/bin/ar",
    },
    "//conditions:default": {},
})

configure_make(
    name = "thrift",
    autogen = True,
    autogen_command = "bootstrap.sh",
    configure_env_vars = configure_env_vars,
    configure_in_place = True,
    configure_options = [
        "--with-boost=$EXT_BUILD_DEPS/boost",
        "--with-libevent=$EXT_BUILD_DEPS/libevent",
        "--disable-debug",
        "--disable-tests",
        "--disable-tutorial",
        "--disable-shared",
        "--without-erlang",
        "--without-haskell",
        "--without-perl",
        "--without-ruby",
        "--without-python",
        "--without-php",
    ],
    lib_source = "@apache_thrift//:all",
    make_commands = [
        "make -j `nproc`",
        "make install",
    ],
    out_static_libs = ["libthrift.a"],
    deps = [
        "@boost",
        "@libevent",
    ],
)
