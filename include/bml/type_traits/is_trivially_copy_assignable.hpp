//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
