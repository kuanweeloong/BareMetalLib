//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_constructible.hpp"
#include "add_lvalue_reference.hpp"
#include "add_const.hpp"

namespace bml
{
    //
    // See std::is_copy_constructible.
    //
    template <typename T>
    struct is_copy_constructible : is_constructible<T, add_lvalue_reference_ty<add_const_ty<T>>> {};
    
    //
    // See std::is_copy_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_copy_constructible_v = bool(is_copy_constructible<T>::value);
}
