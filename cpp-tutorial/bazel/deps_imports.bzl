load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
load("@compressor//bazel:repositories.bzl", "repositories")
load("@compressor//bazel:deps_imports.bzl", "easycompressor_deps")

def dependency_imports():
    rules_foreign_cc_dependencies()
    protobuf_deps()
    boost_deps()
    rules_cc_dependencies()
    repositories()
    easycompressor_deps()
