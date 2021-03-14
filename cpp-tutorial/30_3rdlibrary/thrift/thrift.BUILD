# https://khjtony.github.io/programming/2018/12/31/Add-external-library-to-bazel.html
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")


licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cmake_external(
     name = "thrift",
     binaries = [
         "thrift",
     ],
     cache_entries = {
         "BUILD_TESTING": "OFF",
         "BUILD_TUTORIALS": "OFF",
         "BUILD_C_GLIB": "OFF",
         "BUILD_JAVA": "OFF",
         "THRIFT_COMPILER_C_GLIB": "OFF",
         "THRIFT_COMPILER_D": "OFF",
         "OPENSSL_ROOT_DIR": "$EXT_BUILD_DEPS/openssl",
         "LIBEVENT_ROOT": "$EXT_BUILD_DEPS/libevent",
     },
     lib_source = "@apache_thrift//:all",
    #  tools_deps = [
    #      ":bison-bin",
    #  ],
     deps = [
         "@boost_org//:boost",
         "@libevent//:libevent",
         "@openssl//:openssl",
         "@org_gnu_bison//:bison",
     ],
 )