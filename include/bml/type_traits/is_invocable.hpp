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
#include "invoke_result.hpp"
#include "is_detected.hpp"

namespace bml
{
    namespace detail::is_invocable_detail
    {
        template <typename T>
        using type_member_alias = typename T::type;
    }
    
    //
    // See std::is_invocable.
    //
    template <typename Fn, typename... ArgTypes>
    struct is_invocable : is_detected<detail::is_invocable_detail::type_member_alias,
        invoke_result<Fn, ArgTypes...>> {};
    
    //
    // See std::is_invocable_v.
    //
    template <typename Fn, typename... ArgTypes>
    inline constexpr auto is_invocable_v = bool(is_invocable<Fn, ArgTypes...>::value);
}
