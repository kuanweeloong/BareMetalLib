//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_move_constructible.hpp"
#include "../type_traits/is_move_assignable.hpp"
#include "../type_traits/is_detected.hpp"
#include "../type_traits/add_lvalue_reference.hpp"
#include "move.hpp"
#include "declval.hpp"

namespace bml
{
    template <typename T>
    constexpr auto swap(T& x, T& y) noexcept
        -> enable_if_ty<is_move_constructible_v<T> && is_move_assignable_v<T>>
    {
        auto t = T(bml::move(x));
        x = bml::move(y);
        y = bml::move(t);
    }
    
    // Forward declaration of the swap overload for array to allow swap_ranges to deal with nested
    // arrays.
    template <typename T>
    struct is_swappable;
    
    template <typename T, ::ptrdiff_t N>
    constexpr auto swap(T (&x)[N], T (&y)[N]) noexcept -> enable_if_ty<is_swappable<T>::value>;

    template <typename ForwardIt1, typename ForwardIt2>
    constexpr auto swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) noexcept
        -> ForwardIt2
    {
        while (first1 != last1)
        {
            // Note: ADL for swap explicitly wanted here to find user-defined swaps.
            swap(*first1, *first2);
            
            static_cast<void>(++first1);
            static_cast<void>(++first2);
        }
        
        return first2;
    }
    
    template <typename T, ::ptrdiff_t N>
    constexpr auto swap(T (&x)[N], T (&y)[N]) noexcept -> enable_if_ty<is_swappable<T>::value>
    {
        static_cast<void>(bml::swap_ranges(x, x + N, y));
    }
    
    namespace detail::is_swappable_with_detail
    {
        // Note: ADL for swap is explicitly wanted here to find user-defined swaps.
        template <typename T, typename U>
        using check = decltype(swap(bml::declval<T>(), bml::declval<U>()));
    }
    
    template <typename T, typename U>
    struct is_swappable_with : bool_constant<
           is_detected_v<detail::is_swappable_with_detail::check, T, U>
        && is_detected_v<detail::is_swappable_with_detail::check, U, T>>
    {};
    
    template <typename T, typename U>
    inline constexpr auto is_swappable_with_v = bool(is_swappable_with<T, U>::value);
    
    template <typename T>
    struct is_swappable
        : is_swappable_with<add_lvalue_reference_ty<T>, add_lvalue_reference_ty<T>> {};
    
    template <typename T>
    inline constexpr auto is_swappable_v = bool(is_swappable<T>::value);
}
