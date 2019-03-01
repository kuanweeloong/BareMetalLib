//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_trivially_move_assignable.hpp>

template <typename T>
auto check_trivially_move_assignable() noexcept -> void
{
    static_assert(bml::is_trivially_move_assignable<T>::value);
    static_assert(bml::is_trivially_move_assignable_v<T>);
}

template <typename T>
auto check_not_trivially_move_assignable() noexcept -> void
{
    static_assert(!bml::is_trivially_move_assignable<T>::value);
    static_assert(!bml::is_trivially_move_assignable_v<T>);
}

struct empty {};

union empty_union {};

struct explicit_copy
{
    auto operator=(explicit_copy const&) -> explicit_copy&;
};

struct explicit_move
{
    auto operator=(explicit_move&&) -> explicit_move&;
};

struct copy_ctor
{
    copy_ctor(copy_ctor const&);
};

struct move_ctor
{
    move_ctor(move_ctor&&);
};

class private_move
{
    auto operator=(private_move&&) -> private_move&;
};

struct no_move
{
    auto operator=(no_move&&) -> no_move& = delete;
};

struct nested_no_move
{
    no_move n;
};

class abstract
{
    virtual auto foo() -> void = 0;
};

class abstract_dtor
{
    virtual ~abstract_dtor() = 0;
};

struct const_mem
{
    int const i;
};

struct ref_mem
{
    int& i;
};

struct defaulted_move_assign
{
    auto operator=(defaulted_move_assign&&) -> defaulted_move_assign& = default;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is trivially move assignable.
    {
        check_trivially_move_assignable<int>();
        check_trivially_move_assignable<int&>();
        check_trivially_move_assignable<int*>();
        check_trivially_move_assignable<int const*>();
        check_trivially_move_assignable<double>();
        
        check_trivially_move_assignable<empty>();
        check_trivially_move_assignable<empty_union>();
        check_trivially_move_assignable<copy_ctor>();
        check_trivially_move_assignable<defaulted_move_assign>();
        check_trivially_move_assignable<bmltb::enum_class>();
        check_trivially_move_assignable<bmltb::incomplete_class*>();
        
        check_trivially_move_assignable<int bmltb::class_type::*>();
        check_trivially_move_assignable<int bmltb::incomplete_class::*>();
        check_trivially_move_assignable<int abstract::*>();
        check_trivially_move_assignable<int abstract_dtor::*>();
        
        check_trivially_move_assignable<auto (*)() -> void>();
        check_trivially_move_assignable<auto (*)() noexcept -> void>();
        
        check_trivially_move_assignable<auto (bmltb::class_type::*)() -> void>();
        check_trivially_move_assignable<auto (bmltb::class_type::*)() const && -> void>();
        check_trivially_move_assignable<auto (bmltb::class_type::*&)() const volatile & -> void>();
    }
    
    // Check that the result is false when the input type is not trivially move assignable.
    {
        check_not_trivially_move_assignable<explicit_copy>();
        check_not_trivially_move_assignable<explicit_move>();
        check_not_trivially_move_assignable<abstract>();
        check_not_trivially_move_assignable<abstract_dtor>();
    }
    
    // Check that the result is false when the input type is not move assignable.
    {
        check_not_trivially_move_assignable<void>();
        check_not_trivially_move_assignable<void const>();
        check_not_trivially_move_assignable<void volatile>();
        check_not_trivially_move_assignable<void const volatile>();
        
        check_not_trivially_move_assignable<int const>();
        check_not_trivially_move_assignable<int const&>();
        
        check_not_trivially_move_assignable<char[]>();
        check_not_trivially_move_assignable<char const[]>();
        check_not_trivially_move_assignable<char[][3]>();
        check_not_trivially_move_assignable<char const volatile[][3]>();
        
        check_not_trivially_move_assignable<move_ctor>();
        check_not_trivially_move_assignable<private_move>();
        check_not_trivially_move_assignable<no_move>();
        check_not_trivially_move_assignable<nested_no_move>();
        check_not_trivially_move_assignable<const_mem>();
        check_not_trivially_move_assignable<ref_mem>();
        check_not_trivially_move_assignable<empty const>();
        check_not_trivially_move_assignable<empty_union const>();
        check_not_trivially_move_assignable<defaulted_move_assign const>();
        
        check_not_trivially_move_assignable<auto (&)() -> void>();
        check_not_trivially_move_assignable<auto (&)() noexcept -> void>();
        
        check_not_trivially_move_assignable<auto () -> void>();
        check_not_trivially_move_assignable<auto () noexcept -> void>();
        check_not_trivially_move_assignable<auto () const volatile & noexcept -> void>();
        check_not_trivially_move_assignable<auto () const && noexcept -> void>();
    }
    
    return 0;
}
