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
#include "../../../true_type.hpp"

// Bring in primary template.
#include "../../is_integral_base.hpp"

// When they're available, libc++ always treats __int128_t and __uint128_t as integral types.
// See: https://quuxplusone.github.io/blog/2019/02/28/is-int128-integral/
#if defined(__SIZEOF_INT128__ )
    namespace bml::detail::is_integral_detail
    {
        template <> struct impl<__int128_t>  : true_type {};
        template <> struct impl<__uint128_t> : true_type {};
    }
#endif
