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
#include <stddef.h>
#include "../../../bool_constant.hpp"
#include "../../../true_type.hpp"
#include "../../../false_type.hpp"

namespace bml::detail::is_constructible_detail
{
    // GCC's __is_constructible intrinsic incorrectly reports that arrays with unknown bounds are
    // default constructible, so we handle that case separately.
    
    template <typename T>
    struct is_array_with_unknown_bounds : false_type {};
    
    template <typename T>
    struct is_array_with_unknown_bounds<T[]> : true_type {};
    
    template <typename T, ::ptrdiff_t N>
    struct is_array_with_unknown_bounds<T[N]> : is_array_with_unknown_bounds<T> {};
    
    template <typename T, typename... Args>
    constexpr auto get_constructability() noexcept -> bool
    {
        if (sizeof...(Args) == 0 && is_array_with_unknown_bounds<T>::value)
        {
            // The caller is checking if an array with unknown bounds is default constructible.
            // Manually return false.
            return false;
        }
        else
        {
            return __is_constructible(T, Args...);
        }
    }
    
    template <typename T, typename... Args>
    struct impl : bool_constant<get_constructability<T, Args...>()> {};
}
