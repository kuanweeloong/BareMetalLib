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
#include "is_member_pointer.hpp"
#include "is_member_function_pointer.hpp"

namespace bml
{
    template <typename T>
    struct is_member_object_pointer
        : bool_constant<is_member_pointer_v<T> && !is_member_function_pointer_v<T>> {};

    template <typename T>
    inline constexpr auto is_member_object_pointer_v = bool(is_member_object_pointer<T>::value);
}
