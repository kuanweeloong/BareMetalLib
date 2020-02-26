//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "true_type.hpp"
#include "false_type.hpp"
#include "is_detected.hpp"
#include "is_unbounded_array.hpp"
#include "is_reference.hpp"
#include "is_function.hpp"
#include "is_void.hpp"
#include "is_scalar.hpp"
#include "remove_all_extents.hpp"
#include "../utilities/declval.hpp"

namespace bml
{
    namespace detail::is_destructible_detail
    {
        template <typename T>
        using destructor = decltype(bml::declval<T&>().~T());
        
        template <typename T,
            bool = is_function_v<T> || is_void_v<T> || is_unbounded_array_v<T>,
            bool = is_reference_v<T> || is_scalar_v<T>>
        struct impl : is_detected<destructor, remove_all_extents_ty<T>> {};
        
        template <typename T, bool B>
        struct impl<T, true, B> : false_type {};
        
        template <typename T, bool B>
        struct impl<T, B, true> : true_type {};
    }
    
    template <typename T>
    struct is_destructible : detail::is_destructible_detail::impl<T> {};

    template <typename T>
    inline constexpr auto is_destructible_v = bool(is_destructible<T>::value);
}
