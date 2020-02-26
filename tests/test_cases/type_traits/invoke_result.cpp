//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/invoke_result.hpp>
#include <bml/detail/INVOKE.hpp>
#include <bml/utilities/declval.hpp>
#include <bml/utilities/reference_wrapper.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_detected.hpp>

template <typename Fn, typename... ArgTypes>
auto check_result() noexcept -> void
{
    using Expected = decltype(bml::detail::INVOKE(bml::declval<Fn>(), bml::declval<ArgTypes>()...));
    
    static_assert(bml::is_same_v<typename bml::invoke_result<Fn, ArgTypes...>::type, Expected>);
    static_assert(bml::is_same_v<bml::invoke_result_ty<Fn, ArgTypes...>, Expected>);
}

template <typename T>
using type_member_alias = typename T::type;

template <typename Fn, typename... ArgTypes>
using valid_invoke_result_ty = bml::invoke_result_ty<Fn, ArgTypes...>;

struct c;

struct func_obj
{
    auto operator()() -> int;
    auto operator()(int) -> char const*;
};

auto test_main() noexcept -> int
{
    // Check that the result names the same type as the type of the expression INVOKE(declval<Fn>(),
    // declval<ArgTypes>()...).
    {
        // Pointer to member functions.
        check_result<auto (c::*)(int) -> void, c, int>();
        check_result<auto (c::*)(int) & -> double, c&, int>();
        check_result<auto (c::*)(int) const volatile -> void, c const volatile&, int>();
        check_result<auto (c::*)(int, char) && -> int const&, c, int, char&>();
        check_result<auto (c::*)(int, char) const & -> int const&, c&, int, char&>();
        check_result<auto (c::*)(...) -> float, c>();
        check_result<auto (c::*)(...) -> float, c, int, int*>();
        
        check_result<auto (c::*)(int) -> void, bml::reference_wrapper<c>, int>();
        check_result<auto (c::*)(int) & -> double, bml::reference_wrapper<c>, int>();
        check_result<auto (c::*)(int) const volatile -> void,
            bml::reference_wrapper<c const volatile>&, int>();
        check_result<auto (c::*)(int, char) const & -> int const&,
            bml::reference_wrapper<c>&&, int, char&>();
        check_result<auto (c::*)(...) -> float, bml::reference_wrapper<c>>();
        check_result<auto (c::*)(...) -> float, bml::reference_wrapper<c>&, int, int*>();
        
        // Pointer to data members.
        check_result<int c::*, c>();
        check_result<char* c::*, c>();
        check_result<bmltb::class_type c::*, c>();
        
        check_result<int c::*, bml::reference_wrapper<c>>();
        check_result<char* c::*, bml::reference_wrapper<c>>();
        check_result<bmltb::class_type c::*, bml::reference_wrapper<c>>();
        
        // Free functions.
        check_result<auto () -> void>();
        check_result<auto (&)() -> char>();
        check_result<auto (*)() -> int const&>();
        check_result<auto (*&)() -> int const volatile&&>();
        
        check_result<auto (int) -> void, int>();
        check_result<auto (int) -> void, int&>();
        check_result<auto (&)(int) -> char**, int>();
        check_result<auto (*)(int) -> const char*, int>();
        check_result<auto (*)(int) -> const char*, int&>();
        
        check_result<auto (...) -> void>();
        check_result<auto (...) -> void, int, int&, char>();
        check_result<auto (&)(...) -> char**>();
        check_result<auto (*)(...) -> const char*, int, char&&, int[3]>();
        
        // Function objects
        check_result<func_obj>();
        check_result<func_obj&>();
        
        check_result<func_obj, int>();
        check_result<func_obj&, int>();
    }
    
    // Check that there is no member "type" when INVOKE(declval<Fn>(), declval<ArgTypes>()...) is
    // not well-formed.
    {
        static_assert(!bml::is_detected_v<type_member_alias,
            bml::invoke_result<auto (c::*)(int) -> void>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, auto (c::*)(int) -> void>);
        
        static_assert(!bml::is_detected_v<type_member_alias,
            bml::invoke_result<auto (c::*)(...) -> int>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, auto (c::*)(...) -> int>);
        
        static_assert(!bml::is_detected_v<type_member_alias,
            bml::invoke_result<auto (c::*)() & -> int, c>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, auto (c::*)() & -> int, c>);
        
        static_assert(!bml::is_detected_v<type_member_alias,
            bml::invoke_result<auto (c::*)() && -> void, bml::reference_wrapper<c>>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, auto (c::*)() && -> void,
            bml::reference_wrapper<c>>);
        
        static_assert(!bml::is_detected_v<type_member_alias,
            bml::invoke_result<auto () -> void, int, int&>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, auto () -> void, int, int&>);
        
        static_assert(!bml::is_detected_v<type_member_alias, bml::invoke_result<func_obj, void*>>);
        static_assert(!bml::is_detected_v<valid_invoke_result_ty, func_obj, void*>);
    }
    
    return 0;
}
