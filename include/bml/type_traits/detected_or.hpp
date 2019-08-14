//
// Copyright (c) 2018 Wee Loong Kuan
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
#include "true_type.hpp"
#include "false_type.hpp"
#include "void_ty.hpp"

namespace bml
{
    namespace detail::detected_or_detail
    {
        template <typename Default, typename AlwaysVoid, template <typename...> typename Op,
            typename... Args>
        struct impl
        {
            using value_ty = false_type;
            using type = Default;
        };

        template <typename Default, template <typename...> typename Op, typename... Args>
        struct impl<Default, void_ty<Op<Args...>>, Op, Args...>
        {
            using value_ty = true_type;
            using type = Op<Args...>;
        };
    }
    
    //
    // See Library Fundamentals TS v3's std::experimental::detected_or, except that this is a struct
    // instead of a type alias, and the member type alias value_t is named value_ty for POSIX
    // compatibility.
    //
    template <typename Default, template <typename...> typename Op, typename... Args>
    struct detected_or : detail::detected_or_detail::impl<Default, void, Op, Args...> {};
    
    //
    // See Library Fundamentals TS v3's std::experimental::detected_or_t, except that this is named
    // detected_or_ty for POSIX compatibility.
    //
    template <typename Default, template <typename...> typename Op, typename... Args>
    using detected_or_ty = typename
        detail::detected_or_detail::impl<Default, void, Op, Args...>::type;
}
