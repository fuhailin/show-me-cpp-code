load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

make(
    name = "pslite",
    lib_source = "@pslite//:all",
    out_include_dir = "include",
    out_lib_dir = "lib",
    static_libraries = [
        "libpslite.a",
    ],
    deps = [
        "@com_google_protobuf//:protobuf_lite",
    ]
)
