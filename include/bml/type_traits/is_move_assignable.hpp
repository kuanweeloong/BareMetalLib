//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_rvalue_reference.hpp"

namespace bml
{
    template <typename T>
    struct is_move_assignable : is_assignable<add_lvalue_reference_ty<T>,
        add_rvalue_reference_ty<T>> {};
    
    template <typename T>
    inline constexpr auto is_move_assignable_v = bool(is_move_assignable<T>::value);
}
