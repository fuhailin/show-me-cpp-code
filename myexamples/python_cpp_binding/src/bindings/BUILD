load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

pybind_extension(
    name = "mycpplib",
    srcs = glob(["mycpplib/*.cpp"]),
    visibility = ["//myexamples/python_cpp_binding/src/python:__pkg__"],
    deps = [
        "//myexamples/python_cpp_binding/lib:mycpplib",
    ],
)
