//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include "is_arithmetic.hpp"
#include "bool_constant.hpp"

namespace bml
{
    namespace detail::is_unsigned_detail
    {
        template <typename T>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (is_arithmetic_v<T>)
            {
                return T(0) < T(-1);
            }
            else
            {
                return false;
            }
        }
    }

    template <typename T>
    struct is_unsigned : bool_constant<detail::is_unsigned_detail::check<T>()> {};

    template <typename T>
    inline constexpr auto is_unsigned_v = bool(is_unsigned<T>::value);
}
