//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/pack_size.hpp>

template <typename... Ts>
auto check_size() noexcept -> void
{
    static_assert(bml::pack_size<Ts...>::value == sizeof...(Ts));
    static_assert(bml::pack_size_v<Ts...> == sizeof...(Ts));
}

auto test_main() noexcept -> int
{
    // Check that the result is the same as the output of the sizeof... operator.
    {
        check_size<>();
        
        check_size<int>();
        check_size<int, void>();
        check_size<int, void, char>();
        check_size<int, void, char, char const>();
        check_size<int, void, char, char const, bmltb::class_type[]>();
    }

    return 0;
}
