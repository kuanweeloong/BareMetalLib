//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "pack_size.hpp"
#include "type_pack_element.hpp"
#include "is_constructible.hpp"
#include "is_convertible.hpp"
#include "is_list_convertible.hpp"
#include "bool_constant.hpp"

namespace bml
{
    namespace detail::is_explicitly_constructible_detail
    {
        template <typename T, typename... Args>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (!is_constructible_v<T, Args...>)
            {
                return false;
            }
            else if constexpr (pack_size_v<Args...> == 1)
            {
                using Arg = type_pack_element_ty<0, Args...>;
                return !is_convertible_v<Arg, T>;
            }
            else
            {
                return !is_list_convertible_v<T, Args...>;
            }
        }
    }
    
    template <typename T, typename... Args>
    struct is_explicitly_constructible
        : bool_constant<detail::is_explicitly_constructible_detail::check<T, Args...>()> {};
    
    template <typename T, typename... Args>
    inline constexpr auto is_explicitly_constructible_v =
        bool(is_explicitly_constructible<T, Args...>::value); 
}
