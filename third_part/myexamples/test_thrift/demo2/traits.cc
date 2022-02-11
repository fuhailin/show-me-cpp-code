/*
 * Copyright 2019 curoky(cccuroky@gmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thrift/protocol/TProtocol.h>  // for TProtocol

#include <catch2/catch.hpp>  // for AssertionHandler, operator""_catch_sr, SourceLineInfo, StringRef, REQUIRE, TEST_CASE
#include <type_traits>       // for conditional, false_type, true_type
#include <utility>           // for declval

#include "mock_types.h"  // for MockRequest

namespace details {
template <typename... Ts>
struct helper {};
}  // namespace details

template <class Obj, class = void>
struct is_thrift_object : std::false_type {};

template <class Obj>
struct is_thrift_object<
    Obj, typename std::conditional<
             false,
             details::helper<decltype(std::declval<Obj>().read(
                 (::apache::thrift::protocol::TProtocol*)nullptr))>,
             void>::type> : std::true_type {};

template <class Obj>
constexpr bool is_thrift_object_v = is_thrift_object<Obj>::value;

TEST_CASE("[traits]: judge thrift object") {
  REQUIRE(is_thrift_object_v<int> == false);
  REQUIRE(is_thrift_object_v<idl::thrift::MockRequest> == true);
}
