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
    lib_source = ":all_srcs",
    out_include_dir = "include/opencv4",
    out_shared_libs = select({
        "@platforms//os:macos": [
            "libopencv_core.dylib",
            "libopencv_highgui.dylib",
            "libopencv_imgcodecs.dylib",
            "libopencv_imgproc.dylib",
            "libopencv_dnn.dylib",
            "libopencv_ml.dylib",
            "libopencv_photo.dylib",
            "libopencv_flann.dylib",
            "libopencv_features2d.dylib",
            "libopencv_videoio.dylib",
            "libopencv_calib3d.dylib",
            "libopencv_objdetect.dylib",
            "libopencv_stitching.dylib",
            "libopencv_video.dylib",
            "libopencv_core.4.5.dylib",
        ],
        "@platforms//os:linux": [
            "libopencv_core.so",
            "libopencv_highgui.so",
            "libopencv_imgcodecs.so",
            "libopencv_imgproc.so",
            "libopencv_dnn.so",
            "libopencv_ml.so",
            "libopencv_photo.so",
            "libopencv_flann.so",
            "libopencv_features2d.so",
            "libopencv_videoio.so",
            "libopencv_calib3d.so",
            "libopencv_objdetect.so",
            "libopencv_stitching.so",
            "libopencv_video.so",
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
