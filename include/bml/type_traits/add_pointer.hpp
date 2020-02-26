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
#include "is_void.hpp"
#include "remove_reference.hpp"

namespace bml
{
    namespace detail::add_pointer_detail
    {
        template <typename T, bool = is_void_v<T> || is_referenceable_v<T>>
        struct impl
        {
            using type = T;
        };
        
        template <typename T>
        struct impl<T, true>
        {
            using type = remove_reference_ty<T>*;
        };
    }

    template <typename T>
    struct add_pointer : detail::add_pointer_detail::impl<T> {};

    template <typename T>
    using add_pointer_ty = typename add_pointer<T>::type;
}
