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
    //
    // See std::swap (overload for non-array types).
    //
    template <typename T>
    constexpr auto swap(T& x, T& y) noexcept
        -> enable_if_ty<is_move_constructible_v<T> && is_move_assignable_v<T>>
    {
        T t(bml::move(x));
        x = bml::move(y);
        y = bml::move(t);
    }
    
    // Forward declaration of the swap overload for array to allow swap_ranges to deal with nested
    // arrays.
    template <typename T>
    struct is_swappable;
    
    template <typename T, ::ptrdiff_t N>
    constexpr auto swap(T (&x)[N], T (&y)[N]) noexcept -> enable_if_ty<is_swappable<T>::value>;
    
    //
    // See std::swap_ranges, except that this does not have the overload with ExecutionPolicy.
    //
    template <typename ForwardIt1, typename ForwardIt2>
    constexpr auto swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) noexcept
        -> ForwardIt2
    {
        while (first1 != last1)
        {
            swap(*first1, *first2);
            
            static_cast<void>(++first1);
            static_cast<void>(++first2);
        }
        
        return first2;
    }
    
    //
    // See std::swap (overload for array types), except that this deduces array length as ptrdiff_t
    // instead of size_t. If the array length is negative, the program is ill-formed.
    //
    template <typename T, ::ptrdiff_t N>
    constexpr auto swap(T (&x)[N], T (&y)[N]) noexcept -> enable_if_ty<is_swappable<T>::value>
    {
        static_cast<void>(bml::swap_ranges(x, x + N, y));
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
    
    //
    // See std::is_swappable.
    //
    template <typename T>
    struct is_swappable
        : is_swappable_with<add_lvalue_reference_ty<T>, add_lvalue_reference_ty<T>> {};
    
    //
    // See std::is_swappable_v.
    //
    template <typename T>
    inline constexpr auto is_swappable_v = bool(is_swappable<T>::value);
}
