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

#include <bml_testbench.hpp>
#include <bml/type_traits/is_swappable.hpp>

template <typename T>
auto check_swappable() noexcept -> void
{
    static_assert(bml::is_swappable<T>::value);
    static_assert(bml::is_swappable_v<T>);
}

template <typename T>
auto check_not_swappable() noexcept -> void
{
    static_assert(!bml::is_swappable<T>::value);
    static_assert(!bml::is_swappable_v<T>);
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

struct deleted_swap
{
    friend auto swap(deleted_swap&, deleted_swap&) -> void = delete;
};

namespace
{
    struct ambiguous_swap {};
    
    template <typename T>
    constexpr auto swap(T&, T&) noexcept -> void {}
}

auto test_main() noexcept -> int
{
    // Check that types that can be swapped by bml::swap (i.e. move assignable and move 
    // constructible types) are identified as swappable.
    {
        check_swappable<int>();
        check_swappable<int*>();
        check_swappable<char>();
        check_swappable<double>();
        
        check_swappable<auto (*)() -> void>();
        check_swappable<auto (bmltb::class_type::*)() -> void>();
        
        check_swappable<bmltb::class_type>();
        check_swappable<bmltb::union_type>();
    }
    
    // Check that types which are not swappable via bml::swap, but have a homogeneous user-defined
    // swap taking lvalue references to that type, are identified as swappable.
    {
        check_swappable<user_swap>();
        check_not_swappable<user_swap_rval>();
    }
    
    // Check that types which are not swappable via bml::swap and do not have a user-defined swap
    // are identified as not swappable.
    {
        check_not_swappable<no_swap>();
    }
    
    // Check that types that have a deleted swap are identified as not swappablne.
    {
        check_not_swappable<deleted_swap>();
    }
    
    // Check that types with ambiguous swaps are identified as not swappable.
    {
        check_not_swappable<ambiguous_swap>();
    }
    
    // Check that non-referenceable types are identified as not swappable.
    {
        check_not_swappable<void>();
        check_not_swappable<void const>();
        check_not_swappable<void volatile>();
        check_not_swappable<void const volatile>();
        
        check_not_swappable<auto () const -> void>();
        check_not_swappable<auto () & -> void>();
    }
    
    // Check that is_swappable applies a lvalue reference to the input type.
    {
        check_swappable<int&>();
        check_swappable<int*&>();
        check_swappable<char&>();
        check_swappable<double&>();
        
        // Reference collapse.
        check_not_swappable<user_swap_rval&&>();
        
        check_swappable<int&&>();
        check_swappable<int*&&>();
        check_swappable<char&&>();
        check_swappable<double&&>();
    }
    
    return 0;
}
