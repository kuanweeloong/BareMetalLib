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
#include "is_trivially_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"

namespace bml
{
    //
    // See std::is_trivially_copy_assignable.
    //
    template <typename T>
    struct is_trivially_copy_assignable : is_trivially_assignable<add_lvalue_reference_ty<T>,
        add_lvalue_reference_ty<add_const_ty<T>>> {};
    
    //
    // See std::is_trivially_copy_assignable_v.
    //
    template <typename T>
    inline constexpr auto is_trivially_copy_assignable_v =
        bool(is_trivially_copy_assignable<T>::value);
}
