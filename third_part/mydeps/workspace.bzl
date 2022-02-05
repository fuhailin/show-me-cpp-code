"""Provides a macro to import all dependencies.

Some of the external dependencies need to be initialized. To do this, duplicate
the initialization code from WORKSPACE file.
"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def mydeps_workspace():
    """All external dependencies."""
    pass
