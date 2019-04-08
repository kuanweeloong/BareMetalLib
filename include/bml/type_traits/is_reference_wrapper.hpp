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
#include "remove_cv.hpp"
#include "true_type.hpp"
#include "false_type.hpp"

namespace bml
{
    // Forward declaration of reference_wrapper. This prevents a dependency on the actual
    // reference_wrapper header, which enables functions like INVOKE to use this to detect
    // reference_wrappers while still allowing the actual reference_wrapper code to use INVOKE.
    template <typename T>
    class reference_wrapper;
    
    namespace detail::is_reference_wrapper_detail
    {
        template <typename T> struct impl                       : false_type {};
        template <typename T> struct impl<reference_wrapper<T>> : true_type  {};
    }
    
    //
    // is_reference_wrapper is a unary type trait with a base characteristic of true_type if T is a
    // specialization of reference_wrapper; otherwise, its base characteristic is of false_type.
    //
    template <typename T>
    struct is_reference_wrapper : detail::is_reference_wrapper_detail::impl<remove_cv_ty<T>> {};
    
    //
    // is_reference_wrapper_v is a variable template that yields true if T is a specialization of 
    // reference_wrapper, and false otherwise.
    //
    template <typename T>
    inline constexpr auto is_reference_wrapper_v = bool(is_reference_wrapper<T>::value);
}
