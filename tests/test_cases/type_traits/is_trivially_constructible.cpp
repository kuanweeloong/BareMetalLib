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
#include <bml/type_traits/is_trivially_constructible.hpp>

template <typename... Ts>
auto check_trivially_constructible() noexcept -> void
{
    static_assert(bml::is_trivially_constructible<Ts...>::value);
    static_assert(bml::is_trivially_constructible_v<Ts...>);
}

template <typename... Ts>
auto check_not_trivially_constructible() noexcept -> void
{
    static_assert(!bml::is_trivially_constructible<Ts...>::value);
    static_assert(!bml::is_trivially_constructible_v<Ts...>);
}

struct not_trivial
{
    explicit not_trivial(int);
    not_trivial(int, double);
    not_trivial(int, long, double);
    
private:

    not_trivial(char);
};

struct default_trivial
{
    default_trivial() = default;
    default_trivial(int);
};

struct base {};
struct derived : base {};

class abstract
{
    virtual auto foo() -> void = 0;
};

class abstract_dtor
{
    virtual ~abstract_dtor() = 0;
};

struct private_dtor
{
    private_dtor(int);
    
private:

    ~private_dtor();
}; 

struct template_conv
{
    template <typename T>
    explicit operator T() const;
};

template <typename To>
struct implicit_to
{
    operator To();
};

template <typename To>
struct explicit_to
{
    explicit operator To();
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the 1st type is trivially constructible from the remaining
    // types.
    {
        check_trivially_constructible<int>();
        check_trivially_constructible<int, int>();
        check_trivially_constructible<int, int const>();
        
        check_trivially_constructible<int[2]>();
        check_trivially_constructible<int[2][3]>();
        check_trivially_constructible<int[2][3][5]>();
        
        check_trivially_constructible<int&, int&>();
        check_trivially_constructible<int const&, int>();
        check_trivially_constructible<int const&, int&&>();
        check_trivially_constructible<int&&, double&>();
        
        check_trivially_constructible<default_trivial>();
        
        check_trivially_constructible<base, derived>();
        check_trivially_constructible<base&, derived&>();
        check_trivially_constructible<base const&, derived const&>();
        check_trivially_constructible<base&&, derived>();
        check_trivially_constructible<base&&, derived&&>();
        
        check_trivially_constructible<auto (&)() -> void, auto () -> void>();
        check_trivially_constructible<auto (&)() -> void, auto (&)() -> void>();
        check_trivially_constructible<auto (&)() -> void, auto (&&)() -> void>();
        check_trivially_constructible<auto (&)() noexcept -> void, auto () noexcept -> void>();
        check_trivially_constructible<auto (&)() noexcept -> void, auto (&)() noexcept -> void>();
        check_trivially_constructible<auto (&)() noexcept -> void, auto (&&)() noexcept -> void>();
        
        check_trivially_constructible<auto (&&)() -> void, auto () -> void>();
        check_trivially_constructible<auto (&&)() -> void, auto (&)() -> void>();
        check_trivially_constructible<auto (&&)() -> void, auto (&&)() -> void>();
        check_trivially_constructible<auto (&&)() noexcept -> void, auto () noexcept -> void>();
        check_trivially_constructible<auto (&&)() noexcept -> void, auto (&)() noexcept -> void>();
        check_trivially_constructible<auto (&&)() noexcept -> void, auto (&&)() noexcept -> void>();
        
        check_trivially_constructible<private_dtor&, private_dtor&>();
    }
    
    // Check that the result is false when the 1st type is not trivially constructible from the
    // remaining types.
    {
        check_not_trivially_constructible<not_trivial, int>();
        check_not_trivially_constructible<not_trivial, int const>();
        check_not_trivially_constructible<not_trivial, int, double>();
        check_not_trivially_constructible<not_trivial, int, long, double>();
        
        check_not_trivially_constructible<default_trivial, int>();
        
        check_not_trivially_constructible<int, template_conv>();
        
        check_not_trivially_constructible<int&, implicit_to<int&>>();
        check_not_trivially_constructible<int const&, implicit_to<int>>();
        check_not_trivially_constructible<int const&, implicit_to<int&>>();
        check_not_trivially_constructible<int const&, implicit_to<int&>&>();
        check_not_trivially_constructible<int const&, implicit_to<int&&>>();
        check_not_trivially_constructible<int&&, implicit_to<int&&>>();
        check_not_trivially_constructible<base&&, implicit_to<derived&&>>();
        check_not_trivially_constructible<base&&, implicit_to<derived&&>&>();
        
        check_not_trivially_constructible<int&, explicit_to<int&>>();
        check_not_trivially_constructible<int const&, explicit_to<int&>>();
        check_not_trivially_constructible<int const&, explicit_to<int&>&>();
        check_not_trivially_constructible<int const&, explicit_to<int&&>>();
        check_not_trivially_constructible<int&&, explicit_to<int&&>>();
    }
    
    // Check that the result is false when the 1st type is not constructible from the remaining
    // types.
    {
        check_not_trivially_constructible<int[]>();
        check_not_trivially_constructible<int[][3]>();
        check_not_trivially_constructible<int[][3][5]>();
        
        check_not_trivially_constructible<not_trivial>();
        check_not_trivially_constructible<not_trivial, char>();
        check_not_trivially_constructible<not_trivial, void>();
        
        check_not_trivially_constructible<default_trivial, int, int>();
        
        check_not_trivially_constructible<base&&, base&>();
        check_not_trivially_constructible<base&&, derived&>();
        
        check_not_trivially_constructible<derived, base>();
        check_not_trivially_constructible<derived&, base&>();
        check_not_trivially_constructible<derived const&, base>();
        check_not_trivially_constructible<derived const&, base const&>();
        check_not_trivially_constructible<derived&&, base&&>();
        check_not_trivially_constructible<derived&&, base>();
        
        check_not_trivially_constructible<int, auto () -> void>();
        check_not_trivially_constructible<int, auto () const -> void>();
        check_not_trivially_constructible<int, auto () const noexcept -> void>();
        check_not_trivially_constructible<int, auto () const & -> void>();
        check_not_trivially_constructible<int, auto () && -> void>();
        check_not_trivially_constructible<int, auto (&)() -> void>();
        
        check_not_trivially_constructible<int&>();
        check_not_trivially_constructible<int&, auto () -> void>();
        check_not_trivially_constructible<int&, auto () const -> void>();
        check_not_trivially_constructible<int&, auto () const noexcept -> void>();
        check_not_trivially_constructible<int&, auto () volatile -> void>();
        check_not_trivially_constructible<int&, auto () const & -> void>();
        check_not_trivially_constructible<int&, auto () const && noexcept -> void>();
        check_not_trivially_constructible<int&, auto (&)() -> void>();
        
        check_not_trivially_constructible<auto () -> void>();
        check_not_trivially_constructible<auto () noexcept -> void>();
        check_not_trivially_constructible<auto () volatile -> void>();
        check_not_trivially_constructible<auto () const & -> void>();
        check_not_trivially_constructible<auto () && noexcept -> void>();
        check_not_trivially_constructible<auto () -> void, auto () -> void>();
        check_not_trivially_constructible<auto () const -> void, auto () const -> void>();
        check_not_trivially_constructible<auto () -> void, void*>();
        
        check_not_trivially_constructible<void>();
        check_not_trivially_constructible<void const>();
        check_not_trivially_constructible<void volatile>();
        check_not_trivially_constructible<void const volatile>();
        
        check_not_trivially_constructible<abstract>();
        check_not_trivially_constructible<abstract_dtor>();
        check_not_trivially_constructible<private_dtor, int>();
        
        check_not_trivially_constructible<int&, template_conv>();
        
        check_not_trivially_constructible<int&, explicit_to<double&&>>();
        check_not_trivially_constructible<int const&, explicit_to<double&&>>();
    }
    
    return 0;
}
