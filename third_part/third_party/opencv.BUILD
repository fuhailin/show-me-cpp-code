load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

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
    cache_entries = {
        # "CMAKE_BUILD_TYPE": "RELEASE",
        "BUILD_LIST": "core,highgui,imgproc,videoio,imgcodecs",
        # "WITH_TBB": "OFF",
        # "WITH_IPP": "OFF",
        # "BUILD_DOCS": "OFF",
        # "INSTALL_C_EXAMPLES": "OFF",
        # "INSTALL_PYTHON_EXAMPLES": "OFF",
        # "BUILD_EXAMPLES": "OFF",
        # "BUILD_TESTS": "OFF",
        # "BUILD_PERF_TESTS": "OFF",
        # "WITH_QT": "OFF",
        # "WITH_GTK": "OFF",
        # "WITH_OPENGL": "OFF",
    },
    lib_source = ":all_srcs",
    out_include_dir = "include/opencv4",
    out_shared_libs = select({
        "@platforms//os:macos": [
            # "libopencv_calib3d.dylib",
            "libopencv_core.dylib",
            "libopencv_core.4.5.dylib",
            # "libopencv_dnn.dylib",
            # "libopencv_features2d.dylib",
            # "libopencv_flann.dylib",
            # "libopencv_gapi.dylib",
            "libopencv_highgui.dylib",
            "libopencv_highgui.4.5.dylib",
            "libopencv_imgcodecs.dylib",
            "libopencv_imgcodecs.4.5.dylib",
            "libopencv_imgproc.dylib",
            "libopencv_imgproc.4.5.dylib",
            # "libopencv_java453.dylib",
            # "libopencv_ml.dylib",
            # "libopencv_objdetect.dylib",
            # "libopencv_photo.dylib",
            # "libopencv_stitching.dylib",
            # "libopencv_video.dylib",
            "libopencv_videoio.dylib",
            "libopencv_videoio.4.5.dylib",
        ],
        "@platforms//os:linux": [
            # "libopencv_calib3d.so",
            "libopencv_core.so",
            "libopencv_core.so.4.5",
            # "libopencv_dnn.so",
            # "libopencv_features2d.so",
            # "libopencv_flann.so",
            # "libopencv_gapi.so",
            "libopencv_highgui.so",
            "libopencv_highgui.so.4.5",
            "libopencv_imgcodecs.so",
            "libopencv_imgcodecs.so.4.5",
            "libopencv_imgproc.so",
            "libopencv_imgproc.so.4.5",
            # "libopencv_java453.so",
            # "libopencv_ml.so",
            # "libopencv_objdetect.so",
            # "libopencv_photo.so",
            # "libopencv_stitching.so",
            # "libopencv_video.so",
            "libopencv_videoio.so",
            "libopencv_videoio.so.4.5",
        ],
        "@platforms//os:windows": [
            "libopencv_core.dll",
            "libopencv_highgui.dll",
            "libopencv_imgcodecs.dll",
            "libopencv_imgproc.dll",
            "libopencv_dnn.dll",
            "libopencv_ml.dll",
            "libopencv_photo.dll",
            "libopencv_flann.dll",
            "libopencv_features2d.dll",
            "libopencv_videoio.dll",
            "libopencv_calib3d.dll",
            "libopencv_objdetect.dll",
            "libopencv_stitching.dll",
            "libopencv_video.dll",
        ],
    }),
)