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
#include "is_member_pointer.hpp"
#include "is_member_function_pointer.hpp"

namespace bml
{
    //
    // See std::is_member_object_pointer.
    //
    template <typename T>
    struct is_member_object_pointer
        : bool_constant<is_member_pointer_v<T> && !is_member_function_pointer_v<T>> {};

    //
    // See std::is_member_object_pointer_v.
    //
    template <typename T>
    inline constexpr auto is_member_object_pointer_v = bool(is_member_object_pointer<T>::value);
}
