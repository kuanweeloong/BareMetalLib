//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_function.hpp>

template <typename T>
auto check_function() noexcept -> void
{
    static_assert(bml::is_function<T>::value);
    static_assert(bml::is_function_v<T>);
    
    static_assert(bml::is_function<T const>::value);
    static_assert(bml::is_function_v<T const>);
    
    static_assert(bml::is_function<T volatile>::value);
    static_assert(bml::is_function_v<T volatile>);
    
    static_assert(bml::is_function<T const volatile>::value);
    static_assert(bml::is_function_v<T const volatile>);
}

template <typename T>
auto check_not_function() noexcept -> void
{
    static_assert(!bml::is_function<T>::value);
    static_assert(!bml::is_function_v<T>);
    
    static_assert(!bml::is_function<T const>::value);
    static_assert(!bml::is_function_v<T const>);
    
    static_assert(!bml::is_function<T volatile>::value);
    static_assert(!bml::is_function_v<T volatile>);
    
    static_assert(!bml::is_function<T const volatile>::value);
    static_assert(!bml::is_function_v<T const volatile>);
}

template <typename NoFoo>
struct do_not_instantiate
{
    static constexpr auto x = NoFoo::foo;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a function.
    {
        check_function<auto (int) -> void>();
        check_function<auto (int) -> int>();
        check_function<auto (int, char) noexcept -> void>();
        check_function<auto (int, ...) noexcept -> void>();
        
        check_function<auto (int) & -> void>();
        check_function<auto (char) const & -> void>();
        check_function<auto (double, ...) const && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a function.
    {
        check_not_function<void>();
        check_not_function<int>();
        check_not_function<double>();
        
        check_not_function<int*>();
        check_not_function<int&>();
        check_not_function<int const&>();
        check_not_function<int&&>();
        check_not_function<int volatile*>();
        check_not_function<int[]>();
        check_not_function<int[3]>();
        check_not_function<int(&)[]>();
        check_not_function<int[][2]>();
        
        check_not_function<bmltb::class_type>();
        check_not_function<int bmltb::class_type::*>();
        check_not_function<bmltb::union_type[]>();
        check_not_function<bmltb::enum_class>();
        check_not_function<bmltb::incomplete_class>();
        check_not_function<bmltb::incomplete_class*[][2]>();
        
        check_not_function<auto (&)(int) -> void>();
        check_not_function<auto (*)(int) noexcept -> void>();
        check_not_function<auto (*&&)(int) noexcept -> void>();
        check_not_function<auto (bmltb::class_type::*)() -> void>();
        check_not_function<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that is_function does not instantiate more templates than needed.
    {
        check_not_function<do_not_instantiate<int>*>();
    }

    return 0;
}
