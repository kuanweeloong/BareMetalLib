//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/invoke.hpp>
#include <bml/utilities/reference_wrapper.hpp>
#include <bml/type_traits/is_same.hpp>

struct base
{
    int m_i;
    
    constexpr base() : m_i(42) {}
    
    constexpr auto operator()(int i) const noexcept -> int { return i; }
    constexpr auto operator()(double d) const noexcept -> double { return d; }
};

struct derived : base {};

constexpr auto foo(int i) noexcept -> int
{
    return i;
}

constexpr auto global_derived = derived();

auto test_main() noexcept -> int
{
    // Note: these tests are a simplified version of the tests for INVOKE (detail/INVOKE.cpp), since
    // invoke is basically equivalent to INVOKE. The purpose of these tests is just to act as a
    // quick sanity check; more comprehensive tests are located in INVOKE.cpp.
    
    // Check that pointers to member functions can be invoked.
    {
        constexpr auto d = derived();
        constexpr auto d_ref = bml::reference_wrapper(global_derived);
        
        constexpr auto int_fun = 
            static_cast<auto (base::*)(int) const noexcept -> int>(&base::operator());
        constexpr auto double_fun = 
            static_cast<auto (base::*)(double) const noexcept -> double>(&base::operator());
        
        static_assert(bml::is_same_v<decltype(bml::invoke(int_fun, d, 10)), int>);
        static_assert(bml::invoke(int_fun, d, 10) == 10);
        static_assert(bml::invoke(int_fun, d_ref, 10) == 10);
        
        static_assert(bml::is_same_v<decltype(bml::invoke(double_fun, d, 10.0)), double>);
        static_assert(bml::invoke(double_fun, d, 10.0) == 10.0);
        static_assert(bml::invoke(double_fun, d_ref, 10.0) == 10.0);
    }
    
    // Check that pointers to data members can be invoked.
    {
        constexpr auto d = derived();
        constexpr auto d_ref = bml::reference_wrapper(global_derived);
        constexpr auto mem_ptr = &derived::m_i;
        
        static_assert(bml::is_same_v<decltype(bml::invoke(mem_ptr, d)), int const&>);
        static_assert(bml::invoke(mem_ptr, d) == 42);
        
        static_assert(bml::is_same_v<decltype(bml::invoke(mem_ptr, d_ref)), int const&>);
        static_assert(bml::invoke(mem_ptr, d_ref) == 42);
    }
    
    // Check that free functions can be invoked.
    {
        constexpr auto fun = foo;
        
        static_assert(bml::is_same_v<decltype(bml::invoke(fun, 10)), int>);
        static_assert(bml::invoke(fun, 10) == 10);
    }
    
    // Check that function objects can be invoked.
    {
        constexpr auto d = derived();
        
        static_assert(bml::is_same_v<decltype(bml::invoke(d, 10.0)), double>);
        static_assert(bml::invoke(d, 10.0) == 10.0);
    }

    return 0;
}
