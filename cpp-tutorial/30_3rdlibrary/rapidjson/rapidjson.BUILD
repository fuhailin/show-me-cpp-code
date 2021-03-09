cc_library(
    name = "rapidjson",
    hdrs = glob(["include/rapidjson/**/*.h"]),
    defines = [
        "RAPIDJSON_HAS_STDSTRING",
        "RAPIDJSON_HAS_CXX11_RANGE_FOR",
        "RAPIDJSON_HAS_CXX11_RVALUE_REFS",
        "RAPIDJSON_HAS_CXX11_TYPETRAITS",
        "RAPIDJSON_ASSERT(x)=ENFORCE(x)",
    ],
    includes = ["include"],
    linkstatic = select({
        "@com_stripe_ruby_typer//tools/config:linkshared": 0,
        "//conditions:default": 1,
    }),
    visibility = ["//visibility:public"],
)