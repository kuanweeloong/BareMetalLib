//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "../../../true_type.hpp"

// Bring in primary template.
#include "../../is_integral_base.hpp"

// When they're available, libstdc++ only treats __int128_t and __uint128_t as integral types when
// GNU extensions are enabled.
// See: https://quuxplusone.github.io/blog/2019/02/28/is-int128-integral/
#if defined(__SIZEOF_INT128__ ) && !defined(__STRICT_ANSI__)
    namespace bml::detail::is_integral_detail
    {
        template <> struct impl<__int128_t>  : true_type {};
        template <> struct impl<__uint128_t> : true_type {};
    }
#endif
