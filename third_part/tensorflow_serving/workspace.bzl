"""Provides a macro to import all TensorFlow Serving dependencies.

Some of the external dependencies need to be initialized. To do this, duplicate
the initialization code from TensorFlow Serving's WORKSPACE file.
"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def tf_serving_workspace():
    """All external dependencies."""
    pass
