//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_referenceable.hpp"

namespace bml
{
    namespace detail::add_rvalue_reference_detail
    {
        template <typename T, bool = is_referenceable_v<T>>
        struct impl
        {
            using type = T;
        };
        
        template <typename T>
        struct impl<T, true>
        {
            using type = T&&;
        };
    }

    template <typename T>
    struct add_rvalue_reference : detail::add_rvalue_reference_detail::impl<T> {};

    template <typename T>
    using add_rvalue_reference_ty = typename add_rvalue_reference<T>::type;
}
