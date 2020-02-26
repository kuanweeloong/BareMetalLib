//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_trivially_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"

namespace bml
{
    template <typename T>
    struct is_trivially_copy_assignable : is_trivially_assignable<add_lvalue_reference_ty<T>,
        add_lvalue_reference_ty<add_const_ty<T>>> {};
    
    template <typename T>
    inline constexpr auto is_trivially_copy_assignable_v =
        bool(is_trivially_copy_assignable<T>::value);
}
