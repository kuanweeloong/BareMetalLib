//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    template <typename T> struct is_array                      : false_type {};
    template <typename T> struct is_array<T[]>                 : true_type  {};
    template <typename T, ::ptrdiff_t N> struct is_array<T[N]> : true_type  {};

    template <typename T>
    inline constexpr auto is_array_v = bool(is_array<T>::value);
}
