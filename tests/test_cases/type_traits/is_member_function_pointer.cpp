//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_member_function_pointer.hpp>

template <typename T>
auto check_member_function_pointer() noexcept -> void
{
    static_assert(bml::is_member_function_pointer<T>::value);
    static_assert(bml::is_member_function_pointer_v<T>);
    
    static_assert(bml::is_member_function_pointer<T const>::value);
    static_assert(bml::is_member_function_pointer_v<T const>);
    
    static_assert(bml::is_member_function_pointer<T volatile>::value);
    static_assert(bml::is_member_function_pointer_v<T volatile>);
    
    static_assert(bml::is_member_function_pointer<T const volatile>::value);
    static_assert(bml::is_member_function_pointer_v<T const volatile>);
}

template <typename T>
auto check_not_member_function_pointer() noexcept -> void
{
    static_assert(!bml::is_member_function_pointer<T>::value);
    static_assert(!bml::is_member_function_pointer_v<T>);
    
    static_assert(!bml::is_member_function_pointer<T const>::value);
    static_assert(!bml::is_member_function_pointer_v<T const>);
    
    static_assert(!bml::is_member_function_pointer<T volatile>::value);
    static_assert(!bml::is_member_function_pointer_v<T volatile>);
    
    static_assert(!bml::is_member_function_pointer<T const volatile>::value);
    static_assert(!bml::is_member_function_pointer_v<T const volatile>);
}

using function_ptr = auto (*)() -> void;

struct empty {};

struct abstract
{
    virtual ~abstract() = 0;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a member function pointer.
    {
        check_member_function_pointer<auto (empty::*)() -> void>();
        check_member_function_pointer<auto (abstract::*)() -> void>();
        check_member_function_pointer<auto (bmltb::class_type::*)() -> void>();
        
        check_member_function_pointer<auto (empty::*)(...) & noexcept -> int>();
        check_member_function_pointer<auto (abstract::*)(...) & noexcept -> int>();
        check_member_function_pointer<auto (bmltb::class_type::*)(...) & noexcept -> int>();
        
        check_member_function_pointer<auto (empty::*)() const volatile && noexcept -> void>();
        check_member_function_pointer<auto (abstract::*)() const volatile && noexcept -> void>();
        check_member_function_pointer<
            auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a member function pointer.
    {
        check_not_member_function_pointer<int empty::*>();
        check_not_member_function_pointer<int abstract::*>();
        check_not_member_function_pointer<int bmltb::class_type::*>();
        
        check_not_member_function_pointer<function_ptr empty::*>();
        check_not_member_function_pointer<function_ptr abstract::*>();
        check_not_member_function_pointer<function_ptr bmltb::class_type::*>();
        
        check_not_member_function_pointer<void>();
        check_not_member_function_pointer<int>();
        check_not_member_function_pointer<double>();
        
        check_not_member_function_pointer<int*>();
        check_not_member_function_pointer<int&>();
        check_not_member_function_pointer<int const&>();
        check_not_member_function_pointer<int&&>();
        check_not_member_function_pointer<int volatile*>();
        check_not_member_function_pointer<int[]>();
        check_not_member_function_pointer<int[3]>();
        check_not_member_function_pointer<int(&)[]>();
        check_not_member_function_pointer<int[][2]>();
        
        check_not_member_function_pointer<bmltb::class_type>();
        check_not_member_function_pointer<bmltb::union_type[]>();
        check_not_member_function_pointer<bmltb::enum_class>();
        check_not_member_function_pointer<bmltb::incomplete_class>();
        check_not_member_function_pointer<bmltb::incomplete_class*[][2]>();
        
        check_not_member_function_pointer<auto (int) -> void>();
        check_not_member_function_pointer<auto (int, ...) noexcept -> void>();
        check_not_member_function_pointer<auto (int) & -> void>();
        check_not_member_function_pointer<auto (double, ...) const && noexcept -> void>();
        
        check_not_member_function_pointer<auto (&)(int) -> void>();
        check_not_member_function_pointer<auto (*)(int) noexcept -> void>();
        check_not_member_function_pointer<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
