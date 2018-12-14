//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_constructible.hpp>

template <typename... Ts>
auto check_constructible() noexcept -> void
{
    static_assert(bml::is_constructible<Ts...>::value);
    static_assert(bml::is_constructible_v<Ts...>);
}

template <typename... Ts>
auto check_not_constructible() noexcept -> void
{
    static_assert(!bml::is_constructible<Ts...>::value);
    static_assert(!bml::is_constructible_v<Ts...>);
}

struct test_struct
{
    explicit test_struct(int);
    test_struct(int, double);
    test_struct(int, long, double);
    
private:

    test_struct(char);
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
    // Check that the result is true when the 1st type is constructible from the remaining types.
    {
        check_constructible<int>();
        check_constructible<int, int>();
        check_constructible<int, int const>();
        
        check_constructible<int&, int&>();
        check_constructible<int const&, int>();
        check_constructible<int const&, int&&>();
        check_constructible<int&&, double&>();
        
        check_constructible<test_struct, int>();
        check_constructible<test_struct, int const>();
        check_constructible<test_struct, int, double>();
        check_constructible<test_struct, int, long, double>();
        
        check_constructible<base, derived>();
        check_constructible<base&, derived&>();
        check_constructible<base const&, derived const&>();
        check_constructible<base&&, derived>();
        check_constructible<base&&, derived&&>();
        
        check_constructible<auto (&)() -> void, auto () -> void>();
        check_constructible<auto (&)() -> void, auto (&)() -> void>();
        check_constructible<auto (&)() -> void, auto (&&)() -> void>();
        check_constructible<auto (&)() noexcept -> void, auto () noexcept -> void>();
        check_constructible<auto (&)() noexcept -> void, auto (&)() noexcept -> void>();
        check_constructible<auto (&)() noexcept -> void, auto (&&)() noexcept -> void>();
        
        check_constructible<auto (&&)() -> void, auto () -> void>();
        check_constructible<auto (&&)() -> void, auto (&)() -> void>();
        check_constructible<auto (&&)() -> void, auto (&&)() -> void>();
        check_constructible<auto (&&)() noexcept -> void, auto () noexcept -> void>();
        check_constructible<auto (&&)() noexcept -> void, auto (&)() noexcept -> void>();
        check_constructible<auto (&&)() noexcept -> void, auto (&&)() noexcept -> void>();
        
        check_constructible<private_dtor&, private_dtor&>();
        
        check_constructible<int, template_conv>();
        
        check_constructible<int&, implicit_to<int&>>();
        check_constructible<int const&, implicit_to<int>>();
        check_constructible<int const&, implicit_to<int&>>();
        check_constructible<int const&, implicit_to<int&>&>();
        check_constructible<int const&, implicit_to<int&&>>();
        check_constructible<int&&, implicit_to<int&&>>();
        
        check_constructible<base&&, implicit_to<derived&&>>();
        check_constructible<base&&, implicit_to<derived&&>&>();
        
        check_constructible<int&, explicit_to<int&>>();
        check_constructible<int const&, explicit_to<int&>>();
        check_constructible<int const&, explicit_to<int&>&>();
        check_constructible<int const&, explicit_to<int&&>>();
        check_constructible<int&&, explicit_to<int&&>>();
    }
    
    // Check that the result is false when the 1st type is not constructible from the remaining
    // type.
    {
        check_not_constructible<test_struct>();
        check_not_constructible<test_struct, char>();
        check_not_constructible<test_struct, void>();
        
        check_not_constructible<base&&, base&>();
        check_not_constructible<base&&, derived&>();
        
        check_not_constructible<derived, base>();
        check_not_constructible<derived&, base&>();
        check_not_constructible<derived const&, base>();
        check_not_constructible<derived const&, base const&>();
        check_not_constructible<derived&&, base&&>();
        check_not_constructible<derived&&, base>();
        
        check_not_constructible<int, auto () -> void>();
        check_not_constructible<int, auto () const -> void>();
        check_not_constructible<int, auto () const noexcept -> void>();
        check_not_constructible<int, auto () const & -> void>();
        check_not_constructible<int, auto () && -> void>();
        check_not_constructible<int, auto (&)() -> void>();
        
        check_not_constructible<int&>();
        check_not_constructible<int&, auto () -> void>();
        check_not_constructible<int&, auto () const -> void>();
        check_not_constructible<int&, auto () const noexcept -> void>();
        check_not_constructible<int&, auto () volatile -> void>();
        check_not_constructible<int&, auto () const & -> void>();
        check_not_constructible<int&, auto () const && noexcept -> void>();
        check_not_constructible<int&, auto (&)() -> void>();
        
        check_not_constructible<auto () -> void>();
        check_not_constructible<auto () noexcept -> void>();
        check_not_constructible<auto () volatile -> void>();
        check_not_constructible<auto () const & -> void>();
        check_not_constructible<auto () && noexcept -> void>();
        check_not_constructible<auto () -> void, auto () -> void>();
        check_not_constructible<auto () const -> void, auto () const -> void>();
        check_not_constructible<auto () -> void, void*>();
        
        check_not_constructible<void>();
        check_not_constructible<void const>();
        check_not_constructible<void volatile>();
        check_not_constructible<void const volatile>();
        
        check_not_constructible<abstract>();
        check_not_constructible<abstract_dtor>();
        check_not_constructible<private_dtor, int>();
        
        check_not_constructible<int&, template_conv>();
        
        check_not_constructible<int&, explicit_to<double&&>>();
        check_not_constructible<int const&, explicit_to<double&&>>();
    }
    
    return 0;
}
