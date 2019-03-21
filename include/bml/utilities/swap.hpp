//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_move_constructible.hpp"
#include "../type_traits/is_move_assignable.hpp"
#include "../type_traits/is_detected.hpp"
#include "move.hpp"
#include "declval.hpp"

namespace bml
{
    //
    // See std::swap.
    //
    template <typename T>
    constexpr auto swap(T& x, T& y) noexcept
        -> enable_if_ty<is_move_constructible_v<T> && is_move_assignable_v<T>>
    {
        T t(bml::move(x));
        x = bml::move(y);
        y = bml::move(t);
    }
    
    namespace detail::is_swappable_with_detail
    {
        template <typename T, typename U>
        using check = decltype(swap(declval<T>(), declval<U>()));
    }
    
    //
    // See std::is_swappable_with.
    //
    template <typename T, typename U>
    struct is_swappable_with : bool_constant<
           is_detected_v<detail::is_swappable_with_detail::check, T, U>
        && is_detected_v<detail::is_swappable_with_detail::check, U, T>>
    {};
    
    //
    // See std::is_swappable_with_v.
    //
    template <typename T, typename U>
    inline constexpr auto is_swappable_with_v = bool(is_swappable_with<T, U>::value);
}
