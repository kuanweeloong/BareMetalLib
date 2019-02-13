//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "is_arithmetic.hpp"
#include "bool_constant.hpp"

namespace bml
{
    namespace detail::is_signed_detail
    {
        template <typename T>
        constexpr auto check() noexcept -> bool
        {
            if constexpr (is_arithmetic_v<T>)
            {
                return T(-1) < T(0);
            }
            else
            {
                return false;
            }
        }
    }

    //
    // See std::is_signed.
    //
    template <typename T>
    struct is_signed : bool_constant<detail::is_signed_detail::check<T>()> {};

    //
    // See std::is_signed_v.
    //
    template <typename T>
    inline constexpr auto is_signed_v = bool(is_signed<T>::value);
}
