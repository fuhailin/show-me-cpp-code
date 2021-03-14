https://github.com/Yl4682B4/Blog/blob/660ae10644c43d3c10d0f2e6683df4c7e4eb50d2/Bazel/02.%20用%20Bazel%20构建%20Rocksdb%20项目的实践.md

## 用 Bazel 构建 Rocksdb 项目的实践

为了加深对 Bazel 的理解，这里以一个自己踩了许多坑的实践为例——将 Rocksdb 的官方 Demo （基于 Makefile）改造成 Bazel 项目。

### 获取 Rocksdb 静态库文件与 Demo 项目

`git clone https://github.com/facebook/rocksdb.git `

- 在 `Rocksdb` 根目录下 `make static_lib` 获取 `librocksdb.a` 静态库文件；
- 在 `Rocksdb` 根目录下的 `include/rocksdb/*.h` 获取项目头文件；
- 在 `examples/simple_example.cc` 下，获取项目源文件； 

### 建立 Bazel 项目目录

~~~
- bazel-rocksdb
	- WORKSPACE
	- rocksdb
		- *.h
		- librocksdb.a
		- BUILD
	- demo
		- simple_example.cc
		- BUILD
~~~

大概像这样就可以了，把对应的文件复制过去，然后开始写 BUILD 文件。

### rocksdb BUILD

编辑 rocksdb 目录下的 BUILD 文件。

~~~
load("@rules_cc//cc:defs.bzl", "cc_import")

cc_import(
    name = "rocksdb",
    hdrs = glob(["*.h"]),
    static_library = "librocksdb.a",
    visibility = ["//demo:__pkg__"]
)
~~~

利用 `cc_import()` 规则可以达到引入外部动态/静态链接库的目的，利用 `glob()` 函数可以达到类似 shell 中指定多个文件的目的，再调整 `visibility` 属性让它对 `demo` 这个 package 可见，因为一会儿要依赖他。

现在这个规则就可以直接被其他规则依赖，依赖后可以直接使用 `librocksdb.a` 的实现和引入这里注明了的 `*.h` 头文件。

### demo BUILD

编辑 demo 目录下的 BUILD 文件。

~~~
load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "demo",
	srcs = ["simple_example.cc"],
	deps = ["//rocksdb:rocksdb"],
	copts = ["-fno-rtti -I./ -O2 -std=c++11 -lpthread -lrt -std=c++11  -faligned-new -DHAVE_ALIGNED_NEW -DROCKSDB_PLATFORM_POSIX -DROCKSDB_LIB_IO_POSIX  -DOS_LINUX -fno-builtin-memcmp -DROCKSDB_FALLOCATE_PRESENT -DROCKSDB_MALLOC_USABLE_SIZE -DROCKSDB_PTHREAD_ADAPTIVE_MUTEX -DROCKSDB_BACKTRACE -DROCKSDB_RANGESYNC_PRESENT -DROCKSDB_SCHED_GETCPU_PRESENT -DROCKSDB_AUXV_GETAUXVAL_PRESENT -march=native   -DHAVE_SSE42  -DHAVE_PCLMUL  -DHAVE_AVX2 -DHAVE_UINT128_EXTENSION -DROCKSDB_SUPPORT_THREAD_LOCAL   -ldl -lpthread"],
	linkopts = ["-fno-rtti -I./ -O2 -std=c++11 -lpthread -lrt -std=c++11  -faligned-new -DHAVE_ALIGNED_NEW -DROCKSDB_PLATFORM_POSIX -DROCKSDB_LIB_IO_POSIX  -DOS_LINUX -fno-builtin-memcmp -DROCKSDB_FALLOCATE_PRESENT -DROCKSDB_MALLOC_USABLE_SIZE -DROCKSDB_PTHREAD_ADAPTIVE_MUTEX -DROCKSDB_BACKTRACE -DROCKSDB_RANGESYNC_PRESENT -DROCKSDB_SCHED_GETCPU_PRESENT -DROCKSDB_AUXV_GETAUXVAL_PRESENT -march=native   -DHAVE_SSE42  -DHAVE_PCLMUL  -DHAVE_AVX2 -DHAVE_UINT128_EXTENSION -DROCKSDB_SUPPORT_THREAD_LOCAL   -ldl -lpthread"]

)
~~~

依赖 `rocksdb` 包下的 `rocksdb` target，然后构建为 `demo` target 即可。比较麻烦的是 Rocksdb 项目的构建有较多的编译和链接参数，这里通过 Make 获悉了这些参数的内容，`cc_binary` 的 `copts` 属性用于传递编译参数，`linkopts` 用于传递链接参数，由于懒得区分哪些是哪些，这里就直接都 copy 了一遍。

### 构建项目

`bazel build //demo:demo` 即可。