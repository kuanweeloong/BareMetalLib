//
// Copyright (c) 2018 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    //
    // A variadic version of std::is_same. Checks if T1, T2, Tn... all name the same type.
    //
    template <typename T1, typename T2, typename... Tn>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type  {};

    template <typename T, typename... Ts>
    struct is_same<T, T, Ts...> : is_same<T, Ts...> {};

    //
    // A variadic version of std::is_same_v. Checks if T1, T2, Tn... all name the same type.
    //
    template <typename T1, typename T2, typename... Tn>
    inline constexpr auto is_same_v = bool(is_same<T1, T2, Tn...>::value);
}
