cc_library(
    name = "yaml_internal",
    hdrs = glob(["src/**/*.h"]),
    strip_include_prefix = "src",
)

cc_library(
    name = "yaml",
    srcs = glob([
        "src/**/*.cpp",
        "src/**/*.h",
    ]),
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)
