package(
    default_visibility = ["//mydeps:internal"],
)

licenses(["notice"])

exports_files(["LICENSE"])

# open source marker; do not remove

package_group(
    name = "internal",
    packages = ["//mydeps/..."],
)

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
            "g3doc/sitemap.md",
        ],
    ),
)
