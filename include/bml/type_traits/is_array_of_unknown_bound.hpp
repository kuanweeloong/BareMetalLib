//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    //
    // is_array_of_unknown_bound is a unary type trait with a base characteristic of true_type if T
    // is an array of unknown bound; otherwise, its base characteristic is of false_type.
    //
    template <typename T> struct is_array_of_unknown_bound      : false_type {};
    template <typename T> struct is_array_of_unknown_bound<T[]> : true_type  {};
    
    //
    // is_array_of_unknown_bound_v is a variable template that yields true if T is an array of
    // unknown bound, and false otherwise.
    //
    template <typename T>
    inline constexpr auto is_array_of_unknown_bound_v = bool(is_array_of_unknown_bound<T>::value);
}
