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

    //
    // See std::add_pointer.
    //
    template <typename T>
    struct add_pointer : detail::add_pointer_detail::impl<T> {};

    //
    // See std::add_pointer_t, except that this is named add_pointer_ty for POSIX compatibility.
    //
    template <typename T>
    using add_pointer_ty = typename add_pointer<T>::type;
}
