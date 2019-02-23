//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_volatile.hpp>

template <typename T>
auto check_volatile() noexcept -> void
{
    static_assert(bml::is_volatile<T>::value);
    static_assert(bml::is_volatile_v<T>);
}

template <typename T>
auto check_not_volatile() noexcept -> void
{
    static_assert(!bml::is_volatile<T>::value);
    static_assert(!bml::is_volatile_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is volatile-qualified.
    {
        check_volatile<void volatile>();
        check_volatile<int volatile>();
        check_volatile<double volatile>();
        check_volatile<int volatile[]>();
        check_volatile<int volatile[3]>();
        check_volatile<int* volatile>();
        check_volatile<int volatile* volatile>();
        check_volatile<int(* volatile)[]>();
        
        check_volatile<bmltb::class_type volatile>();
        check_volatile<bmltb::enum_class volatile>();
        check_volatile<bmltb::union_type volatile>();
        check_volatile<bmltb::union_type volatile[]>();
        check_volatile<bmltb::incomplete_class volatile>();
        check_volatile<bmltb::incomplete_class* volatile[][2]>();
        
        check_volatile<bmltb::class_type* volatile>();
        check_volatile<bmltb::incomplete_class* volatile>();
        
        check_volatile<auto (* volatile)(int) noexcept -> void>();
        
        check_volatile<int bmltb::class_type::* volatile>();
        check_volatile<auto (bmltb::class_type::* volatile)() -> void>();
        check_volatile<auto (bmltb::class_type::* volatile)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is true when the input is const-volatile-qualified.
    {
        check_volatile<void const volatile>();
        check_volatile<int const volatile>();
        check_volatile<double const volatile>();
        check_volatile<int const volatile[]>();
        check_volatile<int const volatile[3]>();
        check_volatile<int* const volatile>();
        check_volatile<int const* const volatile>();
        check_volatile<int(* const volatile)[]>();
        check_volatile<int const(* const volatile)[]>();
        
        check_volatile<bmltb::class_type const volatile>();
        check_volatile<bmltb::enum_class const volatile>();
        check_volatile<bmltb::union_type const volatile>();
        check_volatile<bmltb::union_type const volatile[]>();
        check_volatile<bmltb::incomplete_class const volatile>();
        check_volatile<bmltb::incomplete_class* const volatile[][2]>();
        
        check_volatile<bmltb::class_type* const volatile>();
        check_volatile<bmltb::incomplete_class* const volatile>();
        
        check_volatile<auto (* const volatile)(int) noexcept -> void>();
        
        check_volatile<int bmltb::class_type::* const volatile>();
        check_volatile<auto (bmltb::class_type::* const volatile)() -> void>();
        check_volatile<
            auto (bmltb::class_type::* const volatile)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is unqualified.
    {
        check_not_volatile<void>();
        check_not_volatile<int>();
        check_not_volatile<double>();
        check_not_volatile<int[]>();
        check_not_volatile<int[3]>();
        check_not_volatile<int*>();
        check_not_volatile<int const*>();
        check_not_volatile<int(*)[]>();
        check_not_volatile<int const(*)[]>();
        
        check_not_volatile<bmltb::class_type>();
        check_not_volatile<bmltb::enum_class>();
        check_not_volatile<bmltb::union_type>();
        check_not_volatile<bmltb::union_type[]>();
        check_not_volatile<bmltb::incomplete_class>();
        check_not_volatile<bmltb::incomplete_class*[][2]>();
        
        check_not_volatile<bmltb::class_type*>();
        check_not_volatile<bmltb::incomplete_class*>();
        
        check_not_volatile<auto (*)(int) noexcept -> void>();
        
        check_not_volatile<int bmltb::class_type::*>();
        check_not_volatile<auto (bmltb::class_type::*)() -> void>();
        check_not_volatile<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is const-qualified.
    {
        check_not_volatile<void const>();
        check_not_volatile<int const>();
        check_not_volatile<double const>();
        check_not_volatile<int const[]>();
        check_not_volatile<int const[3]>();
        check_not_volatile<int* const>();
        check_not_volatile<int const* const>();
        check_not_volatile<int(* const)[]>();
        check_not_volatile<int const(* const)[]>();
        
        check_not_volatile<bmltb::class_type const>();
        check_not_volatile<bmltb::enum_class const>();
        check_not_volatile<bmltb::union_type const>();
        check_not_volatile<bmltb::union_type const[]>();
        check_not_volatile<bmltb::incomplete_class const>();
        check_not_volatile<bmltb::incomplete_class* const[][2]>();
        
        check_not_volatile<bmltb::class_type* const>();
        check_not_volatile<bmltb::incomplete_class* const>();
        
        check_not_volatile<auto (* const)(int) noexcept -> void>();
        
        check_not_volatile<int bmltb::class_type::* const>();
        check_not_volatile<auto (bmltb::class_type::* const)() -> void>();
        check_not_volatile<
            auto (bmltb::class_type::* const)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input cannot be volatile-qualified.
    {
        check_not_volatile<int&>();
        check_not_volatile<int const&>();
        check_not_volatile<int&&>();
        check_not_volatile<int(&)[]>();
        check_not_volatile<int const(&)[]>();
        
        check_not_volatile<auto (int) -> void>();
        check_not_volatile<auto (int) const && noexcept -> void>();
        check_not_volatile<auto (&)(int) -> void>();
        check_not_volatile<auto (*&&)(int) noexcept -> void>();
        check_not_volatile<auto (* const&&)(int) noexcept -> void>();
    }

    return 0;
}
