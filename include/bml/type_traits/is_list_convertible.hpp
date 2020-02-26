//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../utilities/declval.hpp"
#include "is_detected.hpp"

namespace bml
{
    namespace detail::is_list_convertible_detail
    {
        template <typename T>
        constexpr auto func(T) noexcept -> void;
        
        template <typename T, typename... Args>
        using valid_conv = decltype(is_list_convertible_detail::func<T>({bml::declval<Args>()...}));
    }
    
    template <typename T, typename... Args>
    struct is_list_convertible
        : is_detected<detail::is_list_convertible_detail::valid_conv, T, Args...> {};
    
    template <typename T, typename... Args>
    inline constexpr auto is_list_convertible_v = bool(is_list_convertible<T, Args...>::value); 
}
