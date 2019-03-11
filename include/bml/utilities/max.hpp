//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_same.hpp"

namespace bml
{
    //
    // A variadic version of std::max.
    // 
    // This is different from std::max in that it does not require std::initializer_list to compare
    // more than 2 arguments. In addition, this has an overload to handle a single argument (it just
    // returns a reference to that argument) - the intent is to allow max to be invoked on parameter
    // packs with at least one parameter.
    //
    // Note that T should satisfy LessThanComparable. Also note that the multiple argument version
    // does not participate in overload resolution unless all types in Ts... name the same type as
    // T.
    //
    template <typename T>
    [[nodiscard]] constexpr auto max(T const& a) noexcept -> T const&
    {
        return a;
    }

    template <typename T, typename... Ts>
    [[nodiscard]] constexpr auto max(T const& a1, T const& a2, Ts const&... an) noexcept
        -> enable_if_ty<is_same_v<T, T, Ts...>, T const&>
    {
        auto& curr_max = (a2 < a1) ? a1 : a2;
        return max(curr_max, an...);
    }
}
