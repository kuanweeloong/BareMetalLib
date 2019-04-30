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
    
    //
    // is_explicitly_constructible is a unary type trait with a base characteristic of true_type if
    // T can be constructed from values of type Args... only via an explicit constructor. Otherwise,
    // it has a base characteristic of false_type.
    //
    template <typename T, typename... Args>
    struct is_explicitly_constructible
        : bool_constant<detail::is_explicitly_constructible_detail::check<T, Args...>()> {};
    
    //
    // is_explicitly_constructible_v is a variable template whose value is equal to 
    // is_explicitly_constructible<T, Args...>::value.
    //
    template <typename T, typename... Args>
    inline constexpr auto is_explicitly_constructible_v =
        bool(is_explicitly_constructible<T, Args...>::value); 
}
