# buildifier: disable=module-docstring
load("//third_party/bison:repositories.bzl", bison = "repo")
load("//third_party/cares:repositories.bzl", cares = "repo")
load("//third_party/curl:repositories.bzl", curl = "repo")

# load("//third_party/gn:repositories.bzl", "gn_repositories")
load("//third_party/iconv:repositories.bzl", iconv = "repo")
load("//third_party/libgit2:repositories.bzl", libgit2 = "repo")

# load("//third_party/libpng:repositories.bzl", libpng = "repo")
load("//third_party/libssh2:repositories.bzl", libssh2 = "repo")
load("//third_party/openssl:repositories.bzl", openssl = "repo")
load("//third_party/pcre:repositories.bzl", pcre = "repo")
load("//third_party/cityhash:repositories.bzl", cityhash = "repo")
load("//third_party/openblas:repositories.bzl", openblas = "repo")
load("//third_party/eigen:repositories.bzl", eigen = "repo")
load("//third_party/libevent:repositories.bzl", libevent = "repo")
load("//third_party/googletest:repositories.bzl", googletest = "repo")
load("//third_party/gflags:repositories.bzl", gflags = "repo")
load("//third_party/abseil:repositories.bzl", abseil = "repo")
load("//third_party/msgpack:repositories.bzl", msgpack = "repo")
load("//third_party/jemalloc:repositories.bzl", jemalloc = "repo")
load("//third_party/liburing:repositories.bzl", liburing = "repo")
load("//third_party/db/leveldb:repositories.bzl", leveldb = "repo")
load("//third_party/db/rocksdb:repositories.bzl", rocksdb = "repo")
load("//third_party/db/terarkdb:repositories.bzl", terarkdb = "repo")
load("//third_party/db/hiredis:repositories.bzl", hiredis = "repo")
load("//third_party/logger/glog:repositories.bzl", glog = "repo")
load("//third_party/logger/spdlog:repositories.bzl", spdlog = "repo")
load("//third_party/logger/log4cxx:repositories.bzl", log4cxx = "repo")

# load("//third_party/boost:repositories.bzl", boost = "repo")
load("//third_party/m4:repositories.bzl", m4 = "repo")
load("//third_party/pslite:repositories.bzl", pslite = "repo")

# load("//third_party/rapidcsv:repositories.bzl", "rapidcsv_repo")
load("//third_party/serializer/nlohmann_json:repositories.bzl", nlohmann_json = "repo")
load("//third_party/serializer/flatbuffers:repositories.bzl", flatbuffers = "repo")
load("//third_party/serializer/protobuf:repositories.bzl", protobuf = "repo")
load("//third_party/serializer/thrift:repositories.bzl", thrift = "repo")
load("//third_party/serializer/jbeder_yaml:repositories.bzl", jbeder_yaml = "repo")
load("//third_party/serializer/rapidjson:repositories.bzl", rapidjson = "repo")


load("//third_party/rpc/grpc:repositories.bzl", grpc = "repo")
load("//third_party/rpc/brpc:repositories.bzl", brpc = "repo")
load("//third_party/zeromq:repositories.bzl", zeromq = "repo")
load("//third_party/apr:repositories.bzl", apr = "repo")
load("//third_party/aprutil:repositories.bzl", aprutil = "repo")
load("//third_party/expat:repositories.bzl", expat = "repo")
load(
    "//third_party/rules:repositories.bzl",
    "rules_boost_repo",
    "rules_cc_repo",
    "rules_foreign_cc_repo",
    "rules_jvm_repo",
    "rules_proto_repo",
)
load("//third_party/llvm:repositories.bzl", llvm = "repo")
load("//third_party/zookeeper:repositories.bzl", zookeeper = "repo")
load("//third_party/fmt:repositories.bzl", fmt = "repo")
load("//third_party/double_conversion:repositories.bzl", double_conversion = "repo")
load("//third_party/folly:repositories.bzl", folly = "repo")
load("//third_party/prometheus:repositories.bzl", prometheus = "repo")
load("//third_party/oneTBB:repositories.bzl", oneTBB = "repo")
load("//third_party/EasyCompressor:repositories.bzl", compressor = "repo")
load("//third_party/readerwriterqueue:repositories.bzl", readerwriterqueue = "repo")
load("//third_party/cryptopp:repositories.bzl", cryptopp = "repo")
load("//third_party/sctp:repositories.bzl", sctp = "repo")
load("//third_party/xfs:repositories.bzl", xfs = "repo")
load("//third_party/uuid:repositories.bzl", uuid = "repo")
load("//third_party/seastar:repositories.bzl", seastar = "repo")
load("//third_party/systemtap:repositories.bzl", systemtap = "repo")
load("//third_party/ragel:repositories.bzl", ragel = "repo")
load("//third_party/colm:repositories.bzl", colm = "repo")
load("//third_party/oneDNN:repositories.bzl", oneDNN = "repo")
load("//third_party/pybind11:repositories.bzl", "pybind11_repo", "pybind11_bazel_repo")
load("//third_party/arrow:repositories.bzl", arrow = "repo")
load("//third_party/boringssl:repositories.bzl", boringssl = "repo")
load("//third_party/xsimd:repositories.bzl", xsimd = "repo")
load("//third_party/brotli:repositories.bzl", brotli = "repo")
load("//third_party/boost:repositories.bzl", boost = "repo")
load("//third_party/xz:repositories.bzl", xz = "repo")






def repositories():
    """Load all repositories needed for the targets of rules_foreign_cc_examples_third_party"""

    # load rules
    rules_cc_repo()
    rules_foreign_cc_repo()
    rules_proto_repo()
    # rules_boost_repo()
    rules_jvm_repo()

    # bison_repositories()
    cares()
    curl()

    # gn()
    iconv()
    libgit2()

    # libpng()
    libssh2()
    openssl()
    pcre()
    cityhash()
    openblas()
    eigen()
    libevent()
    googletest()
    gflags()

    abseil()
    msgpack()
    rocksdb()
    terarkdb()
    leveldb()
    jemalloc()
    liburing()

    glog()
    spdlog()
    log4cxx()

    bison()
    m4()
    pslite()
    protobuf()
    thrift()
    zeromq()
    apr()
    aprutil()
    expat()

    nlohmann_json()
    flatbuffers()
    grpc()
    brpc()

    # rapidcsv()
    rapidjson()

    llvm()

    zookeeper()
    hiredis()
    fmt()
    double_conversion()
    folly()
    prometheus()
    oneTBB()
    oneDNN()
    compressor()

    jbeder_yaml()
    readerwriterqueue()
    cryptopp()

    sctp()
    xfs()
    uuid()
    seastar()
    systemtap()
    ragel()
    colm()

    pybind11_repo()
    pybind11_bazel_repo()

    arrow()
    boringssl()
    xsimd()
    brotli()
    boost()
    xz()