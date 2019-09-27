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
#include "../true_type.hpp"
#include "../false_type.hpp"

namespace bml::detail::is_integral_detail
{
    // Provides the primary definition for is_integral's implementation as well as specializations
    // for standard integral types.
    template <typename T> struct impl : false_type {};
    
    template <> struct impl<bool>               : true_type {};
    template <> struct impl<char>               : true_type {};
    template <> struct impl<wchar_t>            : true_type {};
    template <> struct impl<char16_t>           : true_type {};
    template <> struct impl<char32_t>           : true_type {};
    template <> struct impl<signed char>        : true_type {};
    template <> struct impl<unsigned char>      : true_type {};
    template <> struct impl<short>              : true_type {};
    template <> struct impl<unsigned short>     : true_type {};
    template <> struct impl<int>                : true_type {};
    template <> struct impl<unsigned int>       : true_type {};
    template <> struct impl<long>               : true_type {};
    template <> struct impl<unsigned long>      : true_type {};
    template <> struct impl<long long>          : true_type {};
    template <> struct impl<unsigned long long> : true_type {};
}
