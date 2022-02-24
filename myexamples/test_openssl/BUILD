cc_test(
    name = "openssl_test",
    srcs = ["openssl_test.cc"],
    linkopts = select({
        "@openssl//:msvc_compiler": [
            "advapi32.lib",
            "user32.lib",
        ],
        "//conditions:default": [],
    }),
    deps = ["@openssl"],
)
