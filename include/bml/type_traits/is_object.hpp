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
#include "is_scalar.hpp"
#include "is_array.hpp"
#include "is_union.hpp"
#include "is_class.hpp"

namespace bml
{
    template <typename T>
    struct is_object : bool_constant<is_scalar_v<T> || is_array_v<T> || is_union_v<T>
        || is_class_v<T>> {};

    template <typename T>
    inline constexpr auto is_object_v = bool(is_object<T>::value);
}
