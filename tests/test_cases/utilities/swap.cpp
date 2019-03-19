//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/utilities/swap.hpp>
#include <bml/utilities/declval.hpp>
#include <bml/type_traits/is_detected.hpp>

struct not_move_constructible
{
    not_move_constructible() = default;
    
    not_move_constructible(not_move_constructible&&) = delete;
    auto operator=(not_move_constructible&&) -> not_move_constructible& = default;
};

struct not_move_assignable
{
    not_move_assignable() = default;
    
    not_move_assignable(not_move_assignable&&) = default;
    auto operator=(not_move_assignable&&) -> not_move_assignable& = delete;
};

struct not_movable
{
    not_movable() = default;
    
    not_movable(not_movable&&) = delete;
    auto operator=(not_movable&&) -> not_movable& = delete;
};

template <typename T>
using bml_swap_callable = decltype(bml::swap(bml::declval<T>(), bml::declval<T>()));

template <typename T>
constexpr auto swap(T&, T&) -> int { return 100; }

auto test_main() noexcept -> int
{
    // Check that the arguments are swapped.
    {
        static_assert([]() constexpr
        {
            auto i = 10;
            auto j = 20;
            
            bml::swap(i, j);
            
            return i == 20 && j == 10;
        }());
    }
    
    // Check that swap is not callable with non-move-constructible or non-move-assignable types.
    {
        static_assert(bml::is_detected_v<bml_swap_callable, int&>);
        static_assert(bml::is_detected_v<bml_swap_callable, bmltb::class_type&>);
        
        static_assert(!bml::is_detected_v<bml_swap_callable, not_move_constructible&>);
        static_assert(!bml::is_detected_v<bml_swap_callable, not_move_assignable&>);
        static_assert(!bml::is_detected_v<bml_swap_callable, not_movable&>);
    }
    
    // Check that swap does not participate in overload resolution when T is not move-constructible
    // or move-assignable.
    {
        static_assert([]() constexpr
        {
            using bml::swap;
            using ::swap;
            
            not_move_constructible m1;
            not_move_constructible m2;
            
            return swap(m1, m2) == 100;
        }());
        
        static_assert([]() constexpr
        {
            using bml::swap;
            using ::swap;
            
            not_move_assignable m1;
            not_move_assignable m2;
            
            return swap(m1, m2) == 100;
        }());
        
        static_assert([]() constexpr
        {
            using bml::swap;
            using ::swap;
            
            not_movable m1;
            not_movable m2;
            
            return swap(m1, m2) == 100;
        }());
    }
    
    return 0;
}
