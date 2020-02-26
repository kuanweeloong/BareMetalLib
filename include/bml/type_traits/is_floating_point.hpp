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
#include "remove_cv.hpp"

namespace bml
{
    namespace detail::is_floating_point_detail
    {
        template <typename T> struct impl : false_type {};
        
        template <> struct impl<float>       : true_type {};
        template <> struct impl<double>      : true_type {};
        template <> struct impl<long double> : true_type {};
    }
    
    template <typename T>
    struct is_floating_point : detail::is_floating_point_detail::impl<remove_cv_ty<T>> {};

    template <typename T>
    inline constexpr auto is_floating_point_v = bool(is_floating_point<T>::value);
}
