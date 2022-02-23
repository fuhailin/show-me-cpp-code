cc_binary(
    name = "example",
    srcs = [
        "mandelbrot.cpp",
        "pico_bench.hpp",
    ],
    # hdrs = [],
    deps = ["@com_github_xtensorstack_xsimd//:xsimd"],
)

cc_binary(
    name = "main",
    srcs = [
        "main_test.cc",
    ],
    copts = [
        # "-std=c++14",
        "-march=native",
    ],
    deps = ["@com_github_xtensorstack_xsimd//:xsimd"],
)
