load("@rules_foreign_cc//tools/build_defs:boost_build.bzl", "boost_build")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

boost_build(
    name = "boost",
    headers_only = True,
    lib_source = "@boost//:all",
    user_options = ["--with-headers"],
)

# configure_make(
#     name = "bison",
#     binaries = [
#         "bison",
#         "yacc",
#     ],
#     configure_env_vars = configure_env_vars,
#     lib_source = "@bison//:all",
#     static_libraries = [
#         "liby.a",
#     ],
# )
