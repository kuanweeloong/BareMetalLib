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
#include "false_type.hpp"
#include "is_function.hpp"

namespace bml
{
    namespace detail::is_member_function_pointer_detail
    {
        template <typename T>             struct impl         : false_type     {};
        template <typename T, typename U> struct impl<T U::*> : is_function<T> {};
    }
    
    template <typename T>
    struct is_member_function_pointer
        : detail::is_member_function_pointer_detail::impl<remove_cv_ty<T>> {};

    template <typename T>
    inline constexpr auto is_member_function_pointer_v = bool(is_member_function_pointer<T>::value);
}
