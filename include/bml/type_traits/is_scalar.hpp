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
#include "is_arithmetic.hpp"
#include "is_member_pointer.hpp"
#include "is_pointer.hpp"
#include "is_null_pointer.hpp"
#include "is_enum.hpp"

namespace bml
{
    template <typename T>
    struct is_scalar : bool_constant<is_arithmetic_v<T> || is_member_pointer_v<T>
        || is_pointer_v<T> || is_null_pointer_v<T> || is_enum_v<T>> {};

    template <typename T>
    inline constexpr auto is_scalar_v = bool(is_scalar<T>::value);
}
