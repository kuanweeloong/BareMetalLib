//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_constructible.hpp"
#include "add_rvalue_reference.hpp"

namespace bml
{
    //
    // See std::is_move_constructible.
    //
    template <typename T>
    struct is_move_constructible : is_constructible<T, add_rvalue_reference_ty<T>> {};
    
    //
    // See std::is_move_constructible_v.
    //
    template <typename T>
    inline constexpr auto is_move_constructible_v = bool(is_move_constructible<T>::value);
}
