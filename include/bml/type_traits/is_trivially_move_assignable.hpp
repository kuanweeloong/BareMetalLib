//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_trivially_assignable.hpp"
#include "add_lvalue_reference.hpp"
#include "add_rvalue_reference.hpp"

namespace bml
{
    //
    // See std::is_trivially_move_assignable.
    //
    template <typename T>
    struct is_trivially_move_assignable : is_trivially_assignable<add_lvalue_reference_ty<T>,
        add_rvalue_reference_ty<T>> {};
    
    //
    // See std::is_trivially_move_assignable_v.
    //
    template <typename T>
    inline constexpr auto is_trivially_move_assignable_v =
        bool(is_trivially_move_assignable<T>::value);
}
