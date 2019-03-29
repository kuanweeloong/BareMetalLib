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
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    //
    // See std::is_array.
    //
    template <typename T> struct is_array                      : false_type {};
    template <typename T> struct is_array<T[]>                 : true_type  {};
    template <typename T, ::ptrdiff_t N> struct is_array<T[N]> : true_type  {};

    //
    // See std::is_array_v.
    //
    template <typename T>
    inline constexpr auto is_array_v = bool(is_array<T>::value);
}
