//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../detail/INVOKE.hpp"
#include "../utilities/declval.hpp"

namespace bml
{
    namespace detail::invoke_result_detail
    {
        template <typename InvokeRet>
        struct impl
        {
            using type = InvokeRet;
        };
        
        template <>
        struct impl<INVOKE_failure> {};
    }
    
    template <typename Fn, typename... ArgTypes>
    struct invoke_result : detail::invoke_result_detail::impl<
        decltype(detail::INVOKE(bml::declval<Fn>(), bml::declval<ArgTypes>()...))> {};
    
    template <typename Fn, typename... ArgTypes>
    using invoke_result_ty = typename invoke_result<Fn, ArgTypes...>::type;
}
