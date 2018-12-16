//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>
#include "../../../false_type.hpp"
#include "../../../is_constructible.hpp"

namespace bml::detail::is_default_constructible_detail
{
    // GCC's __is_constructible intrinsic doesn't correctly handle arrays with unknown bounds, so we
    // handle it separately.
    
    template <typename T>
    struct is_array_with_unknown_bounds { static constexpr auto value = false; };
    
    template <typename T>
    struct is_array_with_unknown_bounds<T[]> { static constexpr auto value = true; };
    
    template <typename T, ::size_t N>
    struct is_array_with_unknown_bounds<T[N]> : is_array_with_unknown_bounds<T> {};
    
    template <typename T, bool = is_array_with_unknown_bounds<T>::value>
    struct impl : is_constructible<T> {};
    
    template <typename T>
    struct impl<T, true> : false_type {};
}
