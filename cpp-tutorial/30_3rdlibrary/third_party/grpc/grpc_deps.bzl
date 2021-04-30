load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps", "grpc_test_only_deps")
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

def load_grpc_deps():
    

    rules_proto_dependencies()
    rules_proto_toolchains()

    

    grpc_deps()
    grpc_test_only_deps()

    

    grpc_extra_deps()