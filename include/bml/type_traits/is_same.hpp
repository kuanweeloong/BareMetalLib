//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    template <typename T1, typename T2, typename... Tn>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type  {};

    template <typename T, typename... Ts>
    struct is_same<T, T, Ts...> : is_same<T, Ts...> {};

    template <typename T1, typename T2, typename... Tn>
    inline constexpr auto is_same_v = bool(is_same<T1, T2, Tn...>::value);
}
