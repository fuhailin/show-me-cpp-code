# Bazel-gRPC

A demo of how to use gRPC with Bazel.


* No submodules! Instead, we rely on Bazel's external dependency
  support to fetch git remotes.
* Supports C++ only at the moment.


`bazel run greeter_client`

`bazel run greeter_server`


https://medium.com/@pencilflip/getting-started-with-grpc-and-bazel-24725fd9e5c2