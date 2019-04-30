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
#include <bml/type_traits/is_explicitly_constructible.hpp>

template <typename T, typename... Args>
auto check_explicitly_constructible() noexcept -> void
{
    static_assert(bml::is_explicitly_constructible<T, Args...>::value);
    static_assert(bml::is_explicitly_constructible_v<T, Args...>);
}

template <typename T, typename... Args>
auto check_not_explicitly_constructible() noexcept -> void
{
    static_assert(!bml::is_explicitly_constructible<T, Args...>::value);
    static_assert(!bml::is_explicitly_constructible_v<T, Args...>);
}

struct empty {};

struct test_struct
{
    explicit test_struct() {}
    explicit test_struct(float) {}
    explicit test_struct(empty, int) {}
    
    test_struct(empty) {}
    
    test_struct(double) = delete;
    
private:

    test_struct(char, double) {}
    
};

class abstract
{
    virtual auto foo() -> void = 0;
};

struct convertible_to_test_struct
{
    operator test_struct() const { return test_struct(); }
};

auto test_main() noexcept -> int
{
    // Check that the result is true when T is constructible from Args... via an explicit
    // constructor.
    {
        check_explicitly_constructible<test_struct>();
        
        check_explicitly_constructible<test_struct, float>();
        check_explicitly_constructible<test_struct, float const>();
        check_explicitly_constructible<test_struct, float const volatile&>();
        
        check_explicitly_constructible<test_struct, empty, int>();
        check_explicitly_constructible<test_struct, empty, int const volatile>();
        check_explicitly_constructible<test_struct, empty, int const&>();
        check_explicitly_constructible<test_struct, empty&, int volatile>();
        check_explicitly_constructible<test_struct, empty const&, int&>();
    }
    
    // Check that the result is false when T is not constructible from Args....
    {
        check_not_explicitly_constructible<test_struct, double>();
        check_not_explicitly_constructible<test_struct, double const volatile&>();
        check_not_explicitly_constructible<test_struct, char, double>();
        check_not_explicitly_constructible<test_struct, char const volatile, double&>();
        
        check_not_explicitly_constructible<test_struct, void>();
        check_not_explicitly_constructible<test_struct, int>();
        check_not_explicitly_constructible<test_struct, int const volatile>();
        check_not_explicitly_constructible<test_struct, int const&>();
        check_not_explicitly_constructible<test_struct, int, int const>();
        check_not_explicitly_constructible<test_struct, int&, empty>();
        check_not_explicitly_constructible<test_struct, float, empty>();
        
        check_not_explicitly_constructible<test_struct&, test_struct>();
        check_not_explicitly_constructible<test_struct const&, test_struct volatile>();
        check_not_explicitly_constructible<test_struct&, empty, int>();
        check_not_explicitly_constructible<test_struct&, int>();
        
        check_not_explicitly_constructible<void>();
        check_not_explicitly_constructible<void const>();
        check_not_explicitly_constructible<void volatile>();
        check_not_explicitly_constructible<void const volatile>();
        
        check_not_explicitly_constructible<int, auto () -> void>();
        check_not_explicitly_constructible<int[]>();
        check_not_explicitly_constructible<int[][3]>();
        check_not_explicitly_constructible<int&>();
        check_not_explicitly_constructible<int&, int>();
        check_not_explicitly_constructible<int&, auto () -> void>();
        check_not_explicitly_constructible<int*, double*>();
        check_not_explicitly_constructible<auto () -> void>();
        check_not_explicitly_constructible<abstract>();
    }
    
    // Check that the result is false when T can be implicitly constructed from Args....
    {
        check_not_explicitly_constructible<test_struct, empty>();
        check_not_explicitly_constructible<test_struct, empty const volatile&>();
        
        check_not_explicitly_constructible<test_struct, test_struct>();
        check_not_explicitly_constructible<test_struct, test_struct&>();
        check_not_explicitly_constructible<test_struct, test_struct const&>();
        
        check_not_explicitly_constructible<test_struct const&, test_struct>();
        check_not_explicitly_constructible<test_struct&&, test_struct>();
        
        check_not_explicitly_constructible<test_struct, convertible_to_test_struct>();
        check_not_explicitly_constructible<test_struct, convertible_to_test_struct&>();
        check_not_explicitly_constructible<test_struct, convertible_to_test_struct const&>();
        
        check_not_explicitly_constructible<test_struct&, test_struct&>();
        check_not_explicitly_constructible<test_struct&&, test_struct&&>();
        check_not_explicitly_constructible<test_struct const&, test_struct const&>();
        
        check_not_explicitly_constructible<int>();
        check_not_explicitly_constructible<int, int>();
        check_not_explicitly_constructible<int[2]>();
        check_not_explicitly_constructible<int[2][3]>();
        check_not_explicitly_constructible<int&, int&>();
        check_not_explicitly_constructible<int const&, int>();
        check_not_explicitly_constructible<int&&, int>();
        check_not_explicitly_constructible<int&&, double&>();
        check_not_explicitly_constructible<auto (&)() -> void, auto () -> void>();
    }
    
    return 0;
}
