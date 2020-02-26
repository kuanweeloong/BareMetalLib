//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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

    template <typename Default, template <typename...> typename Op, typename... Args>
    struct detected_or : detail::detected_or_detail::impl<Default, void, Op, Args...> {};
    
    template <typename Default, template <typename...> typename Op, typename... Args>
    using detected_or_ty = typename
        detail::detected_or_detail::impl<Default, void, Op, Args...>::type;
}
