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
#include <bml/type_traits/is_invocable.hpp>
#include <bml/utilities/reference_wrapper.hpp>

template <typename Fn, typename... ArgTypes>
auto check_invocable() noexcept -> void
{
    static_assert(bml::is_invocable<Fn, ArgTypes...>::value);
    static_assert(bml::is_invocable_v<Fn, ArgTypes...>);
}

template <typename Fn, typename... ArgTypes>
auto check_not_invocable() noexcept -> void
{
    static_assert(!bml::is_invocable<Fn, ArgTypes...>::value);
    static_assert(!bml::is_invocable_v<Fn, ArgTypes...>);
}

struct c;

struct func_obj
{
    auto operator()() -> int;
    auto operator()(int) -> char const*;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the inputs form an invocable expression.
    {
        // Pointer to member functions.
        check_invocable<auto (c::*)(int) -> void, c, int>();
        check_invocable<auto (c::*)(int) & -> double, c&, int>();
        check_invocable<auto (c::*)(int) const volatile -> void, c const volatile&, int>();
        check_invocable<auto (c::*)(int, char) && -> int const&, c, int, char&>();
        check_invocable<auto (c::*)(int, char) const & -> int const&, c&, int, char&>();
        check_invocable<auto (c::*)(...) -> float, c>();
        check_invocable<auto (c::*)(...) -> float, c, int, int*>();
        
        check_invocable<auto (c::*)(int) -> void, bml::reference_wrapper<c>, int>();
        check_invocable<auto (c::*)(int) & -> double, bml::reference_wrapper<c>, int>();
        check_invocable<auto (c::*)(int) const volatile -> void,
            bml::reference_wrapper<c const volatile>&, int>();
        check_invocable<auto (c::*)(int, char) const & -> int const&,
            bml::reference_wrapper<c>&&, int, char&>();
        check_invocable<auto (c::*)(...) -> float, bml::reference_wrapper<c>>();
        check_invocable<auto (c::*)(...) -> float, bml::reference_wrapper<c>&, int, int*>();
        
        // Pointer to data members.
        check_invocable<int c::*, c>();
        check_invocable<char* c::*, c>();
        check_invocable<bmltb::class_type c::*, c>();
        
        check_invocable<int c::*, bml::reference_wrapper<c>>();
        check_invocable<char* c::*, bml::reference_wrapper<c>>();
        check_invocable<bmltb::class_type c::*, bml::reference_wrapper<c>>();
        
        // Free functions.
        check_invocable<auto () -> void>();
        check_invocable<auto (&)() -> char>();
        check_invocable<auto (*)() -> int const&>();
        check_invocable<auto (*&)() -> int const volatile&&>();
        
        check_invocable<auto (int) -> void, int>();
        check_invocable<auto (int) -> void, int&>();
        check_invocable<auto (&)(int) -> char**, int>();
        check_invocable<auto (*)(int) -> const char*, int>();
        check_invocable<auto (*)(int) -> const char*, int&>();
        
        check_invocable<auto (...) -> void>();
        check_invocable<auto (...) -> void, int, int&, char>();
        check_invocable<auto (&)(...) -> char**>();
        check_invocable<auto (*)(...) -> const char*, int, char&&, int[3]>();
        
        // Function objects
        check_invocable<func_obj>();
        check_invocable<func_obj&>();
        
        check_invocable<func_obj, int>();
        check_invocable<func_obj&, int>();
    }
    
    // Check that the result is false when the inputs do not form an invocable expression.
    {
        check_not_invocable<auto (c::*)(int) -> void>();
        check_not_invocable<auto (c::*)(int) -> void, c>();
        check_not_invocable<auto (c::*)(...) -> int>();
        check_not_invocable<auto (c::*)() & -> int, c>();
        check_not_invocable<auto (c::*)() && -> void, bml::reference_wrapper<c>>();
        check_not_invocable<auto () -> void, int, int&>();
        check_not_invocable<func_obj, void*>();
    }
    
    return 0;
}
