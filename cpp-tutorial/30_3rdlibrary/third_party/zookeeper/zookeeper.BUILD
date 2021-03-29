# vim: ft=bzl

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["zookeeper-client/zookeeper-client-c/**"]),
)

# cmake(
#     name = "zookeeper",
#     lib_source = "@Apache_ZooKeeper//:all",
#     # make_commands = [
#     #     # The correct path to the ninja tool is detected from the selected ninja_toolchain.
#     #     # and "ninja" will be replaced with that path if needed
#     #     "cmake ..",
#     #     "make",
#     # ],
#     working_directory = "zookeeper-client/zookeeper-client-c",
#     # out_include_dir = "include",
#     # out_lib_dir = "lib",
#     # out_static_libs = [
#     #     "libzstd.a",
#     # ],
# )

configure_make(
    name = "zookeeper",
    # autogen = True,
    # autogen_command = " cd $BUILD_TMPDIR/zookeeper-client/zookeeper-client-c",
    # configure_in_place = True,
    lib_source = "@Apache_ZooKeeper//:all",
    # make_commands = [
    #     "make -j `nproc`",
    #     "make install",
    # ],
    # static_libraries = ["liblog4cxx.a"],
    # deps = [
    #     "@apache_apr//:apr",
    #     "@apache_aprutil//:aprutil",vim
    # ],
)
