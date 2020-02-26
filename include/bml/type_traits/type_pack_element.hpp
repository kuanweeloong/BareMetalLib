//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>

namespace bml
{
    namespace detail::type_pack_element_detail
    {
        template <::ptrdiff_t N, typename... Ts>
        struct impl;
    
        template <::ptrdiff_t N, typename Head, typename... Tail>
        struct impl<N, Head, Tail...> : impl<N - 1, Tail...> {};
    
        template <::ptrdiff_t N>
        struct impl<N> {};

        template <typename Head, typename... Tail>
        struct impl<0, Head, Tail...>
        {
            using type = Head;
        };
    }

    template <::ptrdiff_t N, typename... Ts>
    struct type_pack_element : detail::type_pack_element_detail::impl<N, Ts...>
    {
        static_assert(N >= 0, "N cannot be negative.");
    };

    template <::ptrdiff_t N, typename... Ts>
    using type_pack_element_ty = typename type_pack_element<N, Ts...>::type;
}
