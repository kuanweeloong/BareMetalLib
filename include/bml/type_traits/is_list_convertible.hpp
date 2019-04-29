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
#include "../utilities/declval.hpp"
#include "is_detected.hpp"

namespace bml
{
    namespace detail::is_list_convertible_detail
    {
        template <typename T>
        constexpr auto func(T) noexcept -> void;
        
        template <typename T, typename... Args>
        using valid_conv = decltype(is_list_convertible_detail::func<T>({bml::declval<Args>()...}));
    }
    
    //
    // is_list_convertible is a unary type trait with a base characteristic of true_type if the
    // return expression in the following code is well-formed:
    //
    //   T test() {
    //     return {declval<Args>()...};
    //   }
    //
    // Otherwise, it has a base characteristic of false_type.
    //
    // Basically, it tests if T is copy-list-initializable from types named in the template
    // parameter pack Args.
    //
    // Note that T and all types in the template parameter pack Args shall be complete types, cv
    // void, or arrays of unknown bound. Access checking is performed in a context unrelated to T or
    // Args. Only the validity of the immediate context of the expression of the return statement
    // (including initialization of the returned object or reference) is considered.
    //
    template <typename T, typename... Args>
    struct is_list_convertible
        : is_detected<detail::is_list_convertible_detail::valid_conv, T, Args...> {};
    
    //
    // is_list_convertible_v is a variable template whose value is equal to is_list_convertible<T,
    // Args...>::value.
    //
    template <typename T, typename... Args>
    inline constexpr auto is_list_convertible_v = bool(is_list_convertible<T, Args...>::value); 
}
