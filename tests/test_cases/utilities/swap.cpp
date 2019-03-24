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

template <typename T>
using bml_swap_callable = decltype(bml::swap(bml::declval<T>(), bml::declval<T>()));

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

constexpr auto swap(not_move_constructible&, not_move_constructible&) -> int { return 100; }
constexpr auto swap(not_move_assignable&, not_move_assignable&) -> int { return 100; }
constexpr auto swap(not_movable&, not_movable&) -> int { return 100; }

struct not_swappable
{
    not_swappable() = default;
    
    not_swappable(not_swappable&&) = delete;
    auto operator=(not_swappable&&) -> not_swappable& = delete;
};

constexpr auto swap(not_swappable(&)[3], not_swappable(&)[3]) -> int { return 100; }

auto test_main() noexcept -> int
{
    // Check that non-array arguments can be swapped by swap.
    {
        static_assert([]() constexpr
        {
            auto i = 10;
            auto j = 20;
            
            bml::swap(i, j);
            
            return i == 20 && j == 10;
        }());
    }
    
    // Check that array arguments, including those with nested arrays, can be swapped by swap.
    {
        static_assert([]() constexpr
        {
            int i[] = { 10, 20, 30 };
            int j[] = { 40, 50, 60 };
            
            bml::swap(i, j);
            
            return i[0] == 40 && i[1] == 50 && i[2] == 60
                && j[0] == 10 && j[1] == 20 && j[2] == 30;
        }());
        
        
        int i[2][3] = { { 10, 20, 30 },  { 40, 50, 60 } };
        int j[2][3] = { { 100, 200, 300 },  { 400, 500, 600 } };
        
        bml::swap(i, j);
        
        bmltb_assert(i[0][0] == 100);
        bmltb_assert(i[0][1] == 200);
        bmltb_assert(i[0][2] == 300);
        
        bmltb_assert(i[1][0] == 400);
        bmltb_assert(i[1][1] == 500);
        bmltb_assert(i[1][2] == 600);
        
        bmltb_assert(j[0][0] == 10);
        bmltb_assert(j[0][1] == 20);
        bmltb_assert(j[0][2] == 30);
        
        bmltb_assert(j[1][0] == 40);
        bmltb_assert(j[1][1] == 50);
        bmltb_assert(j[1][2] == 60);
    }
    
    // Check that BML's swap is not callable with types that are not move constructible or move
    // assignable.
    {
        static_assert(bml::is_detected_v<bml_swap_callable, int&>);
        static_assert(bml::is_detected_v<bml_swap_callable, bmltb::class_type&>);
        
        static_assert(!bml::is_detected_v<bml_swap_callable, not_move_constructible&>);
        static_assert(!bml::is_detected_v<bml_swap_callable, not_move_assignable&>);
        static_assert(!bml::is_detected_v<bml_swap_callable, not_movable&>);
    }
    
    // Check that BML's swap is not callable with arrays of types that are not swappable (i.e. types
    // that cannot be swapped via the non-array overload of bml::swap, and also do not have a
    // user-defined swap).
    {
        static_assert(bml::is_detected_v<bml_swap_callable, int(&)[2]>);
        static_assert(bml::is_detected_v<bml_swap_callable, int(&)[2][3]>);
        
        static_assert(!bml::is_detected_v<bml_swap_callable, not_swappable(&)[2]>);
        
        // This nested array test case is irritating because we do have a user-defined swap for
        // not_swappable(&)[3] (for a later test), and the array overload of swap has to call
        // swap_ranges, AND swap_ranges has to do ADL for swap. So this fails if the nested array is
        // of length 3.
        static_assert(!bml::is_detected_v<bml_swap_callable, not_swappable(&)[2][4]>);
    }
    
    // Check that swap does not participate in overload resolution when T is not move constructible
    // or move assignable.
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
    
    // Check that the swap not participate in overload resolution when it has array arguments and
    // the underlying array type is not swappable.
    {
        static_assert([]() constexpr
        {
            using bml::swap;
            using ::swap;
            
            not_swappable a[] = { {}, {}, {} };
            not_swappable b[] = { {}, {}, {} };
            
            return swap(a, b) == 100;
        }());
    }
    
    return 0;
}
