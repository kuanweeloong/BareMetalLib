//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
    
    template <typename T, typename U>
    struct is_assignable : bool_constant<detail::is_assignable_detail::impl<T, U>()> {};

    template <typename T, typename U>
    inline constexpr auto is_assignable_v = bool(is_assignable<T, U>::value);
}
