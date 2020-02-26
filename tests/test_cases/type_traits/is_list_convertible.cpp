//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_list_convertible.hpp>

template <typename T, typename... Args>
auto check_list_convertible() noexcept -> void
{
    static_assert(bml::is_list_convertible<T, Args...>::value);
    static_assert(bml::is_list_convertible_v<T, Args...>);
}

template <typename T, typename... Args>
auto check_not_list_convertible() noexcept -> void
{
    static_assert(!bml::is_list_convertible<T, Args...>::value);
    static_assert(!bml::is_list_convertible_v<T, Args...>);
}

enum class int_enum : int { a, b };

struct empty {};

struct aggregate
{
    int i;
    double d;
};

struct test_struct
{
    test_struct() {}
    test_struct(empty) {}
    test_struct(empty, int, int) {}
    
    test_struct(double) = delete;
    
private:

    test_struct(char, double) {}
    
};

auto test_main() noexcept -> int
{
    // Check that the result is true when T can be copy-list-initialized from Args....
    {
        // Via non-narrowing copy-initialization.
        check_list_convertible<int, int>();
        check_list_convertible<int, int const volatile>();
        check_list_convertible<int, char>();
        check_list_convertible<int, char const volatile>();
        check_list_convertible<int&, int&>();
        check_list_convertible<int const volatile&, int volatile&>();
        check_list_convertible<int const&, int>();
        check_list_convertible<int*, int*>();
        check_list_convertible<int const*, int*>();
        check_list_convertible<empty const&, empty>();
        check_list_convertible<aggregate const&, aggregate>();
        
        // Via value-initialization.
        check_list_convertible<int>();
        check_list_convertible<empty>();
        check_list_convertible<test_struct>();
        
        // Via aggregate initialization.
        check_list_convertible<aggregate, int, double>();
        check_list_convertible<aggregate, int const volatile, double const>();
        check_list_convertible<aggregate, int const volatile&, double const&>();
        
        // Via aggregate copy-initialization.
        check_list_convertible<aggregate, aggregate>();
        check_list_convertible<aggregate, aggregate&>();
        check_list_convertible<aggregate, aggregate const&>();
        
        // Via constructor overload resolution.
        check_list_convertible<test_struct, empty>();
        check_list_convertible<test_struct, empty const>();
        check_list_convertible<test_struct, empty, int const, int volatile>();
        check_list_convertible<test_struct, empty&, int const&, int const volatile&>();
        
        // Via list-initialization of temporary.
        check_list_convertible<int const&, char>();
        check_list_convertible<int const&, char const volatile>();
        check_list_convertible<int&&, char>();
        check_list_convertible<int&&, char const volatile>();
        check_list_convertible<int const&>();
        check_list_convertible<int&&>();
        
        check_list_convertible<aggregate const&, int, double>();
        check_list_convertible<aggregate&&, int const volatile, double const>();
        check_list_convertible<empty const&>();
        
        check_list_convertible<test_struct const&>();
        check_list_convertible<test_struct const&, empty>();
        check_list_convertible<test_struct const&, empty const>();
        check_list_convertible<test_struct const&, empty, int const, int volatile>();
    }
    
    // Check that the result is false when T cannot be copy-list-initialized from Args....
    {
        // Conversion failure.
        check_not_list_convertible<void>();
        check_not_list_convertible<void, int>();
        check_not_list_convertible<void, int const&>();
        check_not_list_convertible<int*, double*>();
        check_not_list_convertible<int*&, double*&>();
        
        // Narrowing conversions.
        check_not_list_convertible<double, int>();
        check_not_list_convertible<double const&, int>();
        check_not_list_convertible<int, long long>();
        check_not_list_convertible<int const&, long long>();
        
        // Incompatible references.
        check_not_list_convertible<int&, int>();
        check_not_list_convertible<int&, int const volatile>();
        check_not_list_convertible<int volatile&, int>();
        check_not_list_convertible<int const volatile&, int const volatile>();
        check_not_list_convertible<int const volatile&>();
        
        // Temporary cannot bind to non-const reference.
        check_not_list_convertible<int&>();
        check_not_list_convertible<int&, char>();
        check_not_list_convertible<aggregate&, int const volatile, double const>();
        
        // Enums need direct-list-initialization, not copy-list-initialization.
        check_not_list_convertible<int_enum, int>();
        
        // Constructor overload failure.
        check_not_list_convertible<test_struct, double volatile>();
        check_not_list_convertible<test_struct, bmltb::class_type, int>();
        check_not_list_convertible<test_struct, bmltb::class_type, int const>();
        
        // Deleted constructor.
        check_not_list_convertible<test_struct, double>();
        
        // Inaccessible constructor.
        check_not_list_convertible<test_struct, char, double>();
        
        // Ill formed.
        check_not_list_convertible<void, int const, double, char const, bmltb::class_type>();
    }
    
    return 0;
}
