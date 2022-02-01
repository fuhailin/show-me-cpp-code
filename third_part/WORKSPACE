workspace(name = "tf_serving")

# ===== TensorFlow dependency =====
load("//tensorflow_serving:repo.bzl", "tensorflow_http_archive")

# tensorflow_http_archive(
#     name = "org_tensorflow",
#     git_commit = "58f16dd902fa84f8aa0fd452afb319c1ff65bc74",
#     sha256 = "fcff1657c4cc669597ca5c1945e28e46ff583c86e29e21cc66bc68b4e4a30c73",
# )

local_repository(
    name = "org_tensorflow",
    path = "/Users/vincent/Documents/projects/rules_deps",
)

# Import all of TensorFlow Serving's external dependencies.
# Downstream projects (projects importing TensorFlow Serving) need to
# duplicate all code below in their WORKSPACE file in order to also initialize
# those external dependencies.
load("//tensorflow_serving:workspace.bzl", "tf_serving_workspace")

tf_serving_workspace()

# Initialize TensorFlow's external dependencies.
load("@org_tensorflow//tensorflow:workspace3.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace2.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace1.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace0.bzl", "workspace")

workspace()
