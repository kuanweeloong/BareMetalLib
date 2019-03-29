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
#include "is_scalar.hpp"
#include "is_array.hpp"
#include "is_union.hpp"
#include "is_class.hpp"

namespace bml
{
    //
    // See std::is_object.
    //
    template <typename T>
    struct is_object : bool_constant<is_scalar_v<T> || is_array_v<T> || is_union_v<T>
        || is_class_v<T>> {};

    //
    // See std::is_object_v.
    //
    template <typename T>
    inline constexpr auto is_object_v = bool(is_object<T>::value);
}
