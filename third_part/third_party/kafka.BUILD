load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

# Kafka client dependency used by Kafka-mesh filter.
# librdkafka build generates extra headers that need to be copied into source to get it to compile.
configure_make(
    name = "kafka",
    # args = [
    #     "-j `nproc`",
    # ],
    configure_in_place = True,
    configure_options = ["--disable-ssl --disable-gssapi --disable-lz4-ext --disable-zstd && cp Makefile.config src/.. && cp config.h src/.."],
    lib_source = ":all_srcs",
    linkopts = [
        "-pthread",
        "-ldl",
    ],
    out_static_libs = [
        "librdkafka.a",
        "librdkafka++.a",
    ],
    tags = ["skip_on_windows"],
    targets = [
        "ARFLAGS='' libs install-subdirs",
    ],
    alwayslink = True,
)
