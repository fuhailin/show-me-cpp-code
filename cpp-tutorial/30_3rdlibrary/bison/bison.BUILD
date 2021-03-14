load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

# I tested and this builds only for me on Linux
configure_make(
    name = "bison",
    binaries = [
        "bison",
        "yacc",
    ],
    configure_env_vars = {
        "M4": "$$EXT_BUILD_DEPS$$/m4/bin/m4",
        "CC_FOR_BUILD": "$$CC$$",
    },
    lib_source = "@org_gnu_bison//:all",
    static_libraries = ["liby.a"],
    deps = ["@org_gnu_m4//:m4"],
)
