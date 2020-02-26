//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "bool_constant.hpp"
#include "is_void.hpp"
#include "is_null_pointer.hpp"
#include "is_arithmetic.hpp"

namespace bml
{
    template <typename T>
    struct is_fundamental : bool_constant<is_void_v<T> || is_null_pointer_v<T>
        || is_arithmetic_v<T>> {};

    template <typename T>
    inline constexpr auto is_fundamental_v = bool(is_fundamental<T>::value);
}
