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
#include "../type_traits/add_lvalue_reference.hpp"
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
