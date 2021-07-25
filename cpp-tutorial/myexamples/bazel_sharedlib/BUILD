# cc_binary(
#     name = "libtestStudent.dylib",
#     srcs = ["Student.cpp", "libtestStudent.a"],
#     linkshared = True,
# )

cc_library(
    name = "mylib",
    srcs = ["libtestStudent.dylib"],
    hdrs = ["Student.h"],
)

cc_binary(
    name = "main",
    srcs = ["libtest.cpp"],
    deps = [":mylib"],
)

cc_library(
    name = "mylib",
    srcs = ["libtestStudent.a"],
    hdrs = ["Student.h"],
)

cc_binary(
    name = "main",
    srcs = ["libtest.cpp"],
    #   hrds = ["include/add.h", "include/answer.h"]
    copts = [
        # "-Iinclude/",
        # "-Llib/",
    ],
    linkstatic = 1,
    deps = [":mylib"],
)
