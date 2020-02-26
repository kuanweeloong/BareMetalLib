//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/common_type.hpp>
#include <bml/type_traits/is_detected.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/decay.hpp>
#include <bml/utilities/declval.hpp>

template <typename T>
using type_mem_alias = typename T::type;

template <typename... Ts>
using valid_common_type_ty = bml::common_type_ty<Ts...>;

template <typename... Ts>
auto check_no_type() noexcept
{
    static_assert(!bml::is_detected_v<type_mem_alias, bml::common_type<Ts...>>);
    static_assert(!bml::is_detected_v<valid_common_type_ty, Ts...>);
}

template <typename Expected, typename... Ts>
auto check_result() noexcept
{
    static_assert(bml::is_same_v<Expected, typename bml::common_type<Ts...>::type>);
    static_assert(bml::is_same_v<Expected, bml::common_type_ty<Ts...>>);
}

template <typename T>
auto check_result_decayed() noexcept -> void
{
    check_result<bml::decay_ty<T>, T>();
}

template <typename Expected, typename T1, typename T2>
auto check_result_two() noexcept -> void
{
    check_result<Expected, T1, T2>();
    check_result<Expected, T2, T1>();
    
    check_result<Expected, T1 const, T2>();
    check_result<Expected, T2, T1 const>();
    check_result<Expected, T1, T2 const>();
    check_result<Expected, T2 const, T1>();
    check_result<Expected, T1 const, T2 const>();
    check_result<Expected, T2 const, T1 const>();
    
    check_result<Expected, T1 volatile, T2>();
    check_result<Expected, T2, T1 volatile>();
    check_result<Expected, T1, T2 volatile>();
    check_result<Expected, T2 volatile, T1>();
    check_result<Expected, T1 volatile, T2 volatile>();
    check_result<Expected, T2 volatile, T1 volatile>();
    
    check_result<Expected, T1 const volatile, T2>();
    check_result<Expected, T2, T1 const volatile>();
    check_result<Expected, T1, T2 const volatile>();
    check_result<Expected, T2 const volatile, T1>();
    check_result<Expected, T1 const volatile, T2 const volatile>();
    check_result<Expected, T2 const volatile, T1 const volatile>();
}

template <typename T1, typename T2>
auto check_no_type_two() noexcept -> void
{
    check_no_type<T1, T2>();
    check_no_type<T2, T1>();
    
    check_no_type<T1 const, T2>();
    check_no_type<T2, T1 const>();
    check_no_type<T1, T2 const>();
    check_no_type<T2 const, T1>();
    check_no_type<T1 const, T2 const>();
    check_no_type<T2 const, T1 const>();
    
    check_no_type<T1 volatile, T2>();
    check_no_type<T2, T1 volatile>();
    check_no_type<T1, T2 volatile>();
    check_no_type<T2 volatile, T1>();
    check_no_type<T1 volatile, T2 volatile>();
    check_no_type<T2 volatile, T1 volatile>();
    
    check_no_type<T1 const volatile, T2>();
    check_no_type<T2, T1 const volatile>();
    check_no_type<T1, T2 const volatile>();
    check_no_type<T2 const volatile, T1>();
    check_no_type<T1 const volatile, T2 const volatile>();
    check_no_type<T2 const volatile, T1 const volatile>();
}

struct base {};
struct derived1 : base {};
struct derived2 : base {};

template <typename T>
struct user_spec
{
    // This needs to be explicitly convertible from T to prevent it from being "discovered" by the
    // conditional operator.
    explicit user_spec(T const&) {}
};

namespace bml
{
    template <typename T> struct common_type<T, ::user_spec<T>> { using type = ::user_spec<T>; };
    template <typename T> struct common_type<::user_spec<T>, T> { using type = ::user_spec<T>; };
    
    template <typename T> struct common_type<::user_spec<T>, ::user_spec<T>>
    {
        using type = ::user_spec<T>;
    };
    
    template <> struct common_type<::user_spec<long>, long> {};
    template <> struct common_type<long, ::user_spec<long>> {};
}

auto test_main() noexcept -> int
{
    // Check that there is no type member alias when the input parameter pack is empty.
    {
        check_no_type<>();
    }
    
    // Check that if there is only one input type T, the result names the decayed version of T when
    // there is no user-provided specialization of common_type<T, T>.
    {
        check_result_decayed<void>();
        check_result_decayed<void const>();
        check_result_decayed<void volatile>();
        check_result_decayed<void const volatile>();
        
        check_result_decayed<int>();
        check_result_decayed<int const>();
        check_result_decayed<int[3]>();
        check_result_decayed<int const(&)[3]>();
        check_result_decayed<int const volatile[]>();
        check_result_decayed<int&>();
        check_result_decayed<int&&>();
        check_result_decayed<int const volatile&&>();
        
        check_result_decayed<auto () -> void>();
        check_result_decayed<auto (&)() -> void>();
        check_result_decayed<auto (&&)() -> void>();
        
        check_result_decayed<bmltb::class_type>();
        check_result_decayed<bmltb::union_type>();
        check_result_decayed<auto (bmltb::class_type::*)() -> int>();
    }
    
    // Check that if there are 2 input types T1 and T2, the result names a decayed type which T1 and
    // T2 can be implicitly converted to as-if by the conditional operator.
    {
        check_result_two<int, int, int>();
        check_result_two<int, int, int&&>();
        check_result_two<int, int&, int&>();
        check_result_two<int, int, int const volatile&>();
        check_result_two<int, int const&, int&>();
        
        check_result_two<long, int, long>();
        check_result_two<long, int, long&&>();
        check_result_two<long, int, long const volatile&>();
        check_result_two<long, long&&, int>();
        check_result_two<long, long const volatile&, int>();
        
        check_result_two<double, double, char>();
        check_result_two<double, double, char&&>();
        check_result_two<double, double, char const volatile&>();
        check_result_two<double, double&&, char>();
        check_result_two<double, double const volatile&, char>();
        
        check_result_two<int, short, char>();
        check_result_two<int, short, char&&>();
        check_result_two<int, short, char const volatile&>();
        check_result_two<int, short&&, char>();
        check_result_two<int, short const volatile&, char>();
        
        check_result_two<int*, int*, int*>();
        check_result_two<int const*, int*, int const*>();
        check_result_two<int const*, int const*, int*>();
        check_result_two<int const volatile*, int volatile*, int const*>();
        
        check_result<int*, int[], int[]>();
        check_result<int*, int[], int[3]>();
        check_result<int*, int[2], int[3]>();
        check_result<int const*, int const[], int[3]>();
        check_result<int const*, int[], int const[3]>();
        check_result<int const volatile*, int volatile[], int const[3]>();
        check_result<int const volatile*, int const[], int volatile[3]>();
        
        check_result_two<auto (*)() -> void, auto (*)() -> void, auto (&)() -> void>();
        check_result_two<auto (*)() -> void, auto (*)() -> void, auto (&&)() -> void>();
        check_result_two<auto (*)() -> void, auto (&)() -> void, auto (&&)() -> void>();
        
        check_result_two<bmltb::class_type, bmltb::class_type, bmltb::class_type>();
        check_result_two<bmltb::union_type, bmltb::union_type, bmltb::union_type>();
        check_result_two<auto (bmltb::class_type::*)() -> int, auto (bmltb::class_type::*)() -> int,
            auto (bmltb::class_type::*)() -> int>();
        
        check_result_two<base, base, derived1>();
    }
    
    // Check that if there are 2 input types T1 and T2, but there is no type that T1 and T2 can be
    // implicitly converted to as-if by the conditional operator, there is no type member alias.
    {
        check_no_type_two<int, void>();
        
        check_no_type_two<int[2], double[3]>();
        check_no_type_two<int[], double[3]>();
        check_no_type_two<int[2], double[]>();
        
        check_no_type_two<int*, double*>();
        check_no_type_two<int const volatile*, double*>();
        check_no_type_two<int*, double const volatile*>();
        
        check_no_type_two<int, bmltb::class_type>();
        check_no_type_two<bmltb::class_type, bmltb::union_type>();
        check_no_type_two<auto () -> void, auto (int) -> void>();
        check_no_type_two<auto (bmltb::class_type::*)() -> int, int bmltb::class_type::*>();
        
        check_no_type_two<derived1, derived2>();
    }
    
    // Check that user-provided specializations for two input types are selected over the default
    // implementation.
    {
        // Explicit specializations.
        check_result_two<user_spec<int>, int, user_spec<int>>();
        check_result_two<user_spec<int>, int&, user_spec<int>>();
        check_result_two<user_spec<int>, int, user_spec<int>&>();
        check_result_two<user_spec<int>, int&&, user_spec<int>&&>();
        check_result_two<user_spec<int>, int const volatile&&, user_spec<int>>();
        check_result_two<user_spec<int>, int, user_spec<int> const volatile&&>();
        
        check_result_two<user_spec<int>, user_spec<int>, user_spec<int>>();
        check_result_two<user_spec<int>, user_spec<int>&, user_spec<int>&>();
        check_result_two<user_spec<int>, user_spec<int> volatile&, user_spec<int> const&>();
        check_result_two<user_spec<double>, user_spec<double>, user_spec<double>>();
        
        // Specializations with no type member alias.
        check_no_type_two<user_spec<long>, long>();
        check_no_type_two<user_spec<long>&&, long>();
        check_no_type_two<user_spec<long>, long&&>();
        check_no_type_two<user_spec<long> const volatile&, long>();
        check_no_type_two<user_spec<long>, long const volatile&&>();
        check_no_type_two<user_spec<long> const&, long const&>();
    }
    
    // Check that if there are more than 2 input types, the result is equivalent to performing a
    // left fold on the input with the 2-type specialization of common_type.
    {
        // 3 inputs.
        check_result<int, int, int, int>();
        check_result<int, int const&, int volatile&&, int>();
        check_result<int const volatile*, int volatile*, int const*, int*>();
        
        check_result<long, short, char, long>();
        check_result<long, short const&, char, long volatile&>();
        
        check_result<base, derived1, derived1, base>();
        check_result<base, derived1 const&, derived1, base volatile&&>();
        
        check_result<base, base, derived1, derived2>();
        check_result<base, base, derived2, derived1>();
        check_result<base, derived2, base, derived1>();
        check_result<base, derived1, base, derived2>();
        
        check_result<base, base const&, derived1&&, derived2 const volatile&>();
        check_result<base, base const&, derived2&&, derived1 const volatile&>();
        check_result<base, derived2&&, base, derived1 const volatile&>();
        check_result<base, derived1&&, base, derived2 const volatile&>();
        
        check_result<user_spec<int>, int, user_spec<int>, int>();
        check_result<user_spec<int>, int const&, user_spec<int>&&, int>();
        
        // 3 inputs without a common type.
        check_no_type<int, int, int*>();
        check_no_type<int, int*, int>();
        check_no_type<int*, int, int>();
        
        check_no_type<derived1, derived2, base>();
        check_no_type<derived2, derived1, base>();
        check_no_type<derived2 volatile&&, derived1, base const volatile&>();
        
        check_no_type<user_spec<long>, long, long>();
        check_no_type<user_spec<long>, user_spec<long>, long>();
        check_no_type<user_spec<long>&, user_spec<long>, long const&>();
        
        // 4+ inputs with a common type.
        check_result<int, int, int, int, int>();
        check_result<int, int const&, int volatile&&, int, int const volatile&>();
        
        check_result<base, base, derived1, derived2, derived1>();
        check_result<base, base, derived1, derived2 const&, derived1&&>();
        
        check_result<user_spec<int>, int, user_spec<int>, int, user_spec<int>>();
        check_result<user_spec<int>, int const&, user_spec<int> volatile&, int&, user_spec<int>>();
        
        check_result<int, int, int, int, int, int>();
        check_result<int, int const&, int volatile&&, int, int const volatile&, int>();
        
        check_result<base, base, derived1, derived2, derived1, base>();
        check_result<base, base, derived1, derived2 const&, derived1&&, base>();
        
        check_result<user_spec<int>, int, user_spec<int>, int, user_spec<int>, int>();
        check_result<user_spec<int>, int const&, user_spec<int> volatile&, int&, user_spec<int>,
            int>();
        
        // 4+ inputs without a common type.
        check_no_type<int, int, int*, int>();
        check_no_type<int*, int, int*, int>();
        
        check_no_type<derived1, derived2, base, derived1>();
        check_no_type<derived1&&, derived2 const volatile&, base, derived1&>();
        
        check_no_type<user_spec<long>, long, user_spec<long>, long>();
        check_no_type<user_spec<long>, long const volatile&&, user_spec<long>&, long>();
        
        check_no_type<int, int, int, int, int*>();
        check_no_type<int*, int, int*, int, int*>();
        
        check_no_type<derived1, derived2, base, derived1, derived1>();
        check_no_type<derived1&&, derived2 const volatile&, base, derived1&, derived1&&>();
        
        check_no_type<user_spec<long>, long, user_spec<long>, long, long>();
        check_no_type<user_spec<long>, long const volatile&&, user_spec<long>&, long, long&&>();
    }
    
    return 0;
}
