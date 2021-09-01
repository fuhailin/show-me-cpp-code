load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

cmake(
    name = "opencv",
    build_args = [
        "--verbose",
        "-j `nproc`",
    ],
    build_args = [
        "-GNinja",
        "-DBUILD_LIST=core,highgui,imgcodecs,imgproc",
    ],
    lib_source = ":all_srcs",
    make_commands = [
        "ninja",
        "ninja install",
    ],
    out_include_dir = "include/opencv4",
    out_shared_libs = select({
        "@platforms//os:macos": [
            "libopencv_core.dylib",
            "libopencv_highgui.dylib",
            "libopencv_imgcodecs.dylib",
            "libopencv_imgproc.dylib",
        ],
        "@platforms//os:linux": [
            "libopencv_core.so",
            "libopencv_highgui.so",
            "libopencv_imgcodecs.so",
            "libopencv_imgproc.so",
        ],
        "@platforms//os:windows": [
            "libopencv_core.dll",
            "libopencv_highgui.dll",
            "libopencv_imgcodecs.dll",
            "libopencv_imgproc.dll",
        ],
    }),
    visibility = ["//visibility:public"],
)
