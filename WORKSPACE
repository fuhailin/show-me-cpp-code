workspace(name = "rules_deps_template")

"""
http_archive(
    name = "org_tensorflow",
    strip_prefix = "rules_deps-604b0a38982fcd24d42f8129d4606dd6ac53a334",
    urls = [
        "https://github.com/fuhailin/rules_deps/archive/604b0a38982fcd24d42f8129d4606dd6ac53a334.tar.gz",
    ],
)

"""

local_repository(
    name = "org_tensorflow",
    # path = "/root/projects/rules_deps",
    path = "/Users/vincent/Documents/projects/rules_deps",
)
# """

# Import all of rules_deps's external dependencies.
# Downstream projects need to duplicate all code
# below in their WORKSPACE file in order to also initialize
# those external dependencies.
load("//mydeps:workspace.bzl", "mydeps_workspace")

mydeps_workspace()

# Initialize TensorFlow's external dependencies.
load("@org_tensorflow//tensorflow:workspace3.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace2.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace1.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace0.bzl", "workspace")

workspace()
