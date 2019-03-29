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
#include "is_arithmetic.hpp"
#include "is_member_pointer.hpp"
#include "is_pointer.hpp"
#include "is_null_pointer.hpp"
#include "is_enum.hpp"

namespace bml
{
    //
    // See std::is_scalar.
    //
    template <typename T>
    struct is_scalar : bool_constant<is_arithmetic_v<T> || is_member_pointer_v<T>
        || is_pointer_v<T> || is_null_pointer_v<T> || is_enum_v<T>> {};

    //
    // See std::is_scalar_v.
    //
    template <typename T>
    inline constexpr auto is_scalar_v = bool(is_scalar<T>::value);
}
