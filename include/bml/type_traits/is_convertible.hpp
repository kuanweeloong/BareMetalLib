//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "bool_constant.hpp"
#include "is_array.hpp"
#include "is_void.hpp"
#include "is_function.hpp"
#include "is_detected.hpp"
#include "../utilities/declval.hpp"

namespace bml
{
    namespace detail::is_convertible_detail
    {
        template <typename T>
        auto func(T) -> void;
        
        template <typename From, typename To>
        using valid_conv = decltype(is_convertible_detail::func<To>(bml::declval<From>()));
        
        template <typename From, typename To>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (is_void_v<From> && is_void_v<To>)
            {
                return true;
            }
            else if constexpr (is_array_v<To> || is_function_v<To> || is_void_v<To>)
            {
                return false;
            }
            else
            {
                return is_detected_v<valid_conv, From, To>;
            }
        }
    }
    
    template <typename From, typename To>
    struct is_convertible : bool_constant<detail::is_convertible_detail::check<From, To>()> {};
    
    template <typename From, typename To>
    inline constexpr auto is_convertible_v = bool(is_convertible<From, To>::value);
}
