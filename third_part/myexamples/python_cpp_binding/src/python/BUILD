load("@rules_python//python:defs.bzl", "py_binary")

py_binary(
    name = "bindings_test",
    srcs = ["bindings_test.py"],
    data = ["//myexamples/python_cpp_binding/src/bindings:mycpplib.so"],
    visibility = ["//myexamples/python_cpp_binding/main:__pkg__"],
)
