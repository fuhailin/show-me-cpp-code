load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
# load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
load("@rules_compressor//bazel:repositories.bzl", "rules_compressor_repo")
load("@rules_compressor//bazel:deps_imports.bzl", "rules_compressor_deps")
load("@pybind11_bazel//:python_configure.bzl", "python_configure")

def dependency_imports():
    rules_foreign_cc_dependencies()
    # protobuf_deps()
    # boost_deps()
    rules_cc_dependencies()
    # rules_compressor_repo()
    # rules_compressor_deps()
    # python_configure(name = "local_config_python")
