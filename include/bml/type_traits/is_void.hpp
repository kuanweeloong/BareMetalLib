//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "remove_cv.hpp"
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    namespace detail::is_void_detail
    {
        template <typename T>
        struct impl : false_type {};
        
        template <>
        struct impl<void> : true_type {};
    }
    
    template <typename T>
    struct is_void : detail::is_void_detail::impl<remove_cv_ty<T>> {};

    template <typename T>
    inline constexpr auto is_void_v = bool(is_void<T>::value);
}
