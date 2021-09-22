# vim: ft=bzl
load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

configure_make(
    name = "zookeeper",
    # args = [
    #     "-j `nproc`",
    # ],
    # configure_in_place = True,
    configure_options = [
        "--without-cppunit",
    ],
    # autoreconf = True,
    configure_prefix = "ant clean jar && ant compile_jute && cd zookeeper-client/zookeeper-client-c && autoreconf -if && configure",
    lib_source = ":all_srcs",
    out_static_libs = [
        "libzookeeper_mt.a",
        "libzookeeper_st.a",
    ],
)
