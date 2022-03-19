package(default_visibility = ["//visibility:public"])

[
    cc_binary(
        name = "%s" % f[0:f.rfind(".")],
        srcs = [
            "%s" % f,
        ],
        copts = [
            "-std=gnu++17",
            "-w",
        ],
        deps = [
            "@com_github_facebook_rocksdb//:rocksdb",
        ],
    )
    for f in glob([
        "*.cc",
    ])
]
