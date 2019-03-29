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

namespace bml
{
    //
    // See std::is_const.
    //
    template <typename T> struct is_const          : false_type {};
    template <typename T> struct is_const<T const> : true_type  {};

    //
    // See std::is_const_v.
    //
    template <typename T>
    inline constexpr auto is_const_v = bool(is_const<T>::value);
}
