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
        using valid_conv = decltype(is_convertible_detail::func<To>(declval<From>()));
        
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
    
    //
    // See std::is_convertible.
    //
    template <typename From, typename To>
    struct is_convertible : bool_constant<detail::is_convertible_detail::check<From, To>()> {};
    
    //
    // See std::is_convertible_v.
    //
    template <typename From, typename To>
    inline constexpr auto is_convertible_v = bool(is_convertible<From, To>::value);
}
