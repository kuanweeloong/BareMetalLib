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
    
    //
    // See std::is_floating_point
    //
    template <typename T>
    struct is_floating_point : detail::is_floating_point_detail::impl<remove_cv_ty<T>> {};

    //
    // See std::is_floating_point_v.
    //
    template <typename T>
    inline constexpr auto is_floating_point_v = bool(is_floating_point<T>::value);
}
