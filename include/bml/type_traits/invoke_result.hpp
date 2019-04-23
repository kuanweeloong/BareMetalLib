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
    
    //
    // See std::invoke_result.
    //
    template <typename Fn, typename... ArgTypes>
    struct invoke_result : detail::invoke_result_detail::impl<
        decltype(detail::INVOKE(bml::declval<Fn>(), bml::declval<ArgTypes>()...))> {};
    
    //
    // See std::invoke_result_t, except that this is named invoke_result_ty for POSIX compatibility.
    //
    template <typename Fn, typename... ArgTypes>
    using invoke_result_ty = typename invoke_result<Fn, ArgTypes...>::type;
}
