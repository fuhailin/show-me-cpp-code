load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds only for me on Linux
configure_make(
    name = "log4cxx",
    autogen = True,
    configure_in_place = True,
    configure_options = [
        "--with-apr=$EXT_BUILD_DEPS/apr",
        "--with-apr-util=$EXT_BUILD_DEPS/aprutil",
    ],
    lib_source = "@apache_log4cxx//:all",
    make_commands = [
        "make -j `nproc`",
        "make install",
    ],
    static_libraries = ["liblog4cxx.a"],
    deps = [
        "@apache_apr//:apr",
        "@apache_aprutil//:aprutil",
    ],
)

# https://github.com/hcoona/one/blob/42b23b6c3edde36dc4fc64ed569e4ff86710b0fd/third_party/log4cxx/log4cxx.BUILD
