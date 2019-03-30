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
    
    //
    // This provides a member type alias "type" which names the N-th type in the type parameter pack
    // Ts. If N is larger than or equal to sizeof...(Ts), there is no member type. If N is negative,
    // the program is ill-formed.
    //
    template <::ptrdiff_t N, typename... Ts>
    struct type_pack_element : detail::type_pack_element_detail::impl<N, Ts...>
    {
        static_assert(N >= 0, "N cannot be negative.");
    };
    
    //
    // This is a helper type alias for type_pack_element<N, Ts...>::type.
    //
    template <::ptrdiff_t N, typename... Ts>
    using type_pack_element_ty = typename type_pack_element<N, Ts...>::type;
}
