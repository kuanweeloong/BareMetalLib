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

#pragma once
#include <stddef.h>
#include "integral_constant.hpp"
#include "../detail/size_to_ptrdiff.hpp"

namespace bml
{
    //
    // pack_size is a unary type trait with a base characteristic of integral_constant<ptrdiff_t,
    // Value>, where Value is equivalent to sizeof...(Ts). If sizeof...(Ts) is larger than the
    // maximum value that ptrdiff_t can hold, the program is ill-formed.
    //
    template <typename... Ts>
    struct pack_size : integral_constant<::ptrdiff_t, detail::size_to_ptrdiff<sizeof...(Ts)>()> {};

    //
    // pack_size_v is a variable template of type ptrdiff_t, whose value is equivalent to
    // sizeof...(Ts). If sizeof...(Ts) is larger than the maximum value that ptrdiff_t can hold, the
    // program is ill-formed.
    //
    template <typename... Ts>
    inline constexpr auto pack_size_v = ::ptrdiff_t(pack_size<Ts...>::value);
}
