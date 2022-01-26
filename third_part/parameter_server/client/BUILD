# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary

cc_binary(
    name = "client",
    srcs = glob([
        "include/*.h",
        "src/client.cpp",
    ]),
    copts = ["-Iclinet/include"],
    deps = [
        "@cityhash:cityhash",
        "@cpp3rd_lib//tcmcp",
    ],
)

cc_binary(
    name = "input_fid",
    srcs = glob([
        "include/*.h",
        "src/input_fid.cpp",
    ]),
    copts = ["-Iclinet/include"],
    deps = [
        "@cpp3rd_lib//tcmcp",
        "@cpp3rd_lib//util",
    ],
)

cc_binary(
    name = "validate_fid",
    srcs = glob([
        "include/*.h",
        "src/validate_fid.cpp",
    ]),
    copts = ["-Iclinet/include"],
    deps = [
        "@cpp3rd_lib//tcmcp",
        "@cpp3rd_lib//util",
    ],
)

cc_binary(
    name = "pull",
    srcs = glob([
        "include/*.h",
        "src/pull.cpp",
    ]),
    copts = ["-Iclinet/include"],
    deps = [
        "@cpp3rd_lib//tcmcp",
    ],
)

cc_binary(
    name = "send_cmd_to_ps_offline",
    srcs = glob([
        "include/*.h",
        "src/send_cmd_to_ps_offline.cpp",
    ]),
    copts = ["-Iclinet/include"],
    deps = [
        "@cpp3rd_lib//tcmcp",
    ],
)
