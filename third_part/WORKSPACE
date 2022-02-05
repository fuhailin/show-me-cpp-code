workspace(name = "rules_deps_template")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "org_tensorflow",
    strip_prefix = "rules_deps-c9f5812ceb1db1bb48865900822937a428a1434f",
    urls = [
        "https://github.com/fuhailin/rules_deps/archive/c9f5812ceb1db1bb48865900822937a428a1434f.tar.gz",
    ],
)

# Import all of rules_deps's external dependencies.
# Downstream projects need to duplicate all code
# below in their WORKSPACE file in order to also initialize
# those external dependencies.
load("//mydeps:workspace.bzl", "mydeps_workspace")

mydeps_workspace()

# Initialize TensorFlow's external dependencies.
load("@org_tensorflow//tensorflow:workspace3.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace2.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace1.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace0.bzl", "workspace")

workspace()
