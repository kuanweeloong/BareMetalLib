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
#include "bool_constant.hpp"
#include "is_integral.hpp"
#include "is_floating_point.hpp"

namespace bml
{
    //
    // See std::is_arithmetic, except that implementation-defined integral types are not recognized
    // as arithmetic unless specializations of is_integral is provided for such types.
    //
    template <typename T>
    struct is_arithmetic : bool_constant<is_integral_v<T> || is_floating_point_v<T>> {};

    //
    // See std::is_arithmetic_v.
    //
    template <typename T>
    inline constexpr auto is_arithmetic_v = bool(is_arithmetic<T>::value);
}
