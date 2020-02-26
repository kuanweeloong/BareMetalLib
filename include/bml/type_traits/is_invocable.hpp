//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "invoke_result.hpp"
#include "is_detected.hpp"

namespace bml
{
    namespace detail::is_invocable_detail
    {
        template <typename T>
        using type_member_alias = typename T::type;
    }
    
    template <typename Fn, typename... ArgTypes>
    struct is_invocable : is_detected<detail::is_invocable_detail::type_member_alias,
        invoke_result<Fn, ArgTypes...>> {};
    
    template <typename Fn, typename... ArgTypes>
    inline constexpr auto is_invocable_v = bool(is_invocable<Fn, ArgTypes...>::value);
}
