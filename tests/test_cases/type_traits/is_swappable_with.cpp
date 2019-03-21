//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_swappable_with.hpp>

template <typename T, typename U>
auto check_swappable_with() noexcept -> void
{
    static_assert(bml::is_swappable_with<T, U>::value);
    static_assert(bml::is_swappable_with_v<T, U>);
}

template <typename T, typename U>
auto check_not_swappable_with() noexcept -> void
{
    static_assert(!bml::is_swappable_with<T, U>::value);
    static_assert(!bml::is_swappable_with_v<T, U>);
}

struct user_swap
{
    user_swap(user_swap&&) = delete;
    auto operator=(user_swap&&) -> user_swap& = delete;
};

constexpr auto swap(user_swap&, user_swap&) noexcept -> void {}

struct user_swap_rval
{
    user_swap_rval(user_swap_rval&&) = delete;
    auto operator=(user_swap_rval&&) -> user_swap_rval& = delete;
};

constexpr auto swap(user_swap_rval&&, user_swap_rval&&) noexcept -> void {}

struct no_swap
{
    no_swap(no_swap&&) = delete;
    auto operator=(no_swap&&) -> no_swap& = delete;
};

struct one {};
struct two {};
struct three {};

constexpr auto swap(one&, two&) noexcept -> void {}
constexpr auto swap(two&, one&) noexcept -> void {}

constexpr auto swap(one&, three&) noexcept -> void {}

auto test_main() noexcept -> int
{
    // Check that lvalue references to types that can be swapped by bml::swap (i.e. move assignable
    // and move constructible) are identified as swappable the same type.
    {
        check_swappable_with<int&, int&>();
        check_swappable_with<int*&, int*&>();
        check_swappable_with<char&, char&>();
        check_swappable_with<double&, double&>();
        
        check_swappable_with<bmltb::class_type&, bmltb::class_type&>();
        check_swappable_with<bmltb::union_type&, bmltb::union_type&>();
        
        check_swappable_with<auto (*&)() -> void, auto (*&)() -> void>();
        check_swappable_with<auto (bmltb::class_type::*&)() -> void,
            auto (bmltb::class_type::*&)() -> void>();
    }
    
    // Check that lvalue references to types that can be swapped by bml::swap (i.e. move assignable
    // and move constructible types) are identified as not swappable with a different type when
    // there is no user-defined heterogeneous swap function.
    {
        check_not_swappable_with<int&, bmltb::class_type&>();
        check_not_swappable_with<bmltb::class_type&, int&>();
        
        check_not_swappable_with<int*&, char*&>();
        check_not_swappable_with<char*&, int*&>();
        
        check_not_swappable_with<auto () const && -> void, auto () const && -> void>();
        check_not_swappable_with<auto () const && -> void, auto () && -> void>();
    }
    
    // Check that types which are not swappable via bml::swap, but have a homogeneous user-defined
    // swap, are identified as swappable with itself, but not other types.
    {
        check_swappable_with<user_swap&, user_swap&>();
        check_swappable_with<user_swap_rval, user_swap_rval>();
        
        check_not_swappable_with<user_swap&, int&>();
        check_not_swappable_with<int&, user_swap&>();
        
        check_not_swappable_with<user_swap_rval, int>();
        check_not_swappable_with<int, user_swap_rval>();
    }
    
    // Check that types which are not swappable via bml::swap and do not have a user-defined swap
    // are identified as not swappable.
    {
        check_not_swappable_with<no_swap&, no_swap&>();
        check_not_swappable_with<no_swap&, int&>();
        check_not_swappable_with<int&, no_swap&>();
    }
    
    // Check that types with heterogeneous user-defined swaps are swappable if swaps are defined in
    // both directions (i.e. swap(A, B) and swap(B, A) are defined).
    {
        check_swappable_with<one&, two&>();
        check_swappable_with<two&, one&>();
        
        check_not_swappable_with<one&, three&>();
        check_not_swappable_with<three&, one&>();
    }
    
    // Check that is_swappable_with does not apply lvalue references to the input types.
    {
        check_not_swappable_with<int, int>();
        check_not_swappable_with<int*, int*>();
        check_not_swappable_with<char, char>();
        check_not_swappable_with<double, double>();
        
        check_not_swappable_with<bmltb::class_type, bmltb::class_type>();
        check_not_swappable_with<bmltb::union_type, bmltb::union_type>();
    }
    
    return 0;
}
