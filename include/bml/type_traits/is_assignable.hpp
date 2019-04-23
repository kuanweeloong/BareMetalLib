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
#include "is_detected.hpp"
#include "is_void.hpp"
#include "bool_constant.hpp"
#include "../utilities/declval.hpp"

namespace bml
{
    namespace detail::is_assignable_detail
    {
        template <typename T, typename U>
        using assignment_type = decltype(bml::declval<T>() = bml::declval<U>());
        
        template <typename T, typename U>
        constexpr auto impl() noexcept -> bool
        {
            if (is_void_v<T> || is_void_v<U>)
            {
                return false;
            }
            else 
            {
                return is_detected_v<assignment_type, T, U>;
            }
        }
    }
    
    //
    // See std::is_assignable.
    //
    template <typename T, typename U>
    struct is_assignable : bool_constant<detail::is_assignable_detail::impl<T, U>()> {};

    //
    // See std::is_assignable_v.
    //
    template <typename T, typename U>
    inline constexpr auto is_assignable_v = bool(is_assignable<T, U>::value);
}
