//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_const.hpp>

template <typename T>
auto check_const() noexcept -> void
{
    static_assert(bml::is_const<T>::value);
    static_assert(bml::is_const_v<T>);
}

template <typename T>
auto check_not_const() noexcept -> void
{
    static_assert(!bml::is_const<T>::value);
    static_assert(!bml::is_const_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is const-qualified.
    {
        check_const<void const>();
        check_const<int const>();
        check_const<double const>();
        check_const<int const[]>();
        check_const<int const[3]>();
        check_const<int* const>();
        check_const<int const* const>();
        check_const<int(* const)[]>();
        check_const<int const(* const)[]>();
        
        check_const<bmltb::class_type const>();
        check_const<bmltb::enum_class const>();
        check_const<bmltb::union_type const>();
        check_const<bmltb::union_type const[]>();
        check_const<bmltb::incomplete_class const>();
        check_const<bmltb::incomplete_class* const[][2]>();
        
        check_const<bmltb::class_type* const>();
        check_const<bmltb::incomplete_class* const>();
        
        check_const<auto (* const)(int) noexcept -> void>();
        
        check_const<int bmltb::class_type::* const>();
        check_const<auto (bmltb::class_type::* const)() -> void>();
        check_const<auto (bmltb::class_type::* const)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is true when the input is const-volatile-qualified.
    {
        check_const<void const volatile>();
        check_const<int const volatile>();
        check_const<double const volatile>();
        check_const<int const volatile[]>();
        check_const<int const volatile[3]>();
        check_const<int* const volatile>();
        check_const<int const* const volatile>();
        check_const<int(* const volatile)[]>();
        check_const<int const(* const volatile)[]>();
        
        check_const<bmltb::class_type const volatile>();
        check_const<bmltb::enum_class const volatile>();
        check_const<bmltb::union_type const volatile>();
        check_const<bmltb::union_type const volatile[]>();
        check_const<bmltb::incomplete_class const volatile>();
        check_const<bmltb::incomplete_class* const volatile[][2]>();
        
        check_const<bmltb::class_type* const volatile>();
        check_const<bmltb::incomplete_class* const volatile>();
        
        check_const<auto (* const volatile)(int) noexcept -> void>();
        
        check_const<int bmltb::class_type::* const volatile>();
        check_const<auto (bmltb::class_type::* const volatile)() -> void>();
        check_const<
            auto (bmltb::class_type::* const volatile)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is unqualified.
    {
        check_not_const<void>();
        check_not_const<int>();
        check_not_const<double>();
        check_not_const<int[]>();
        check_not_const<int[3]>();
        check_not_const<int*>();
        check_not_const<int const*>();
        check_not_const<int(*)[]>();
        check_not_const<int const(*)[]>();
        
        check_not_const<bmltb::class_type>();
        check_not_const<bmltb::enum_class>();
        check_not_const<bmltb::union_type>();
        check_not_const<bmltb::union_type[]>();
        check_not_const<bmltb::incomplete_class>();
        check_not_const<bmltb::incomplete_class*[][2]>();
        
        check_not_const<bmltb::class_type*>();
        check_not_const<bmltb::incomplete_class*>();
        
        check_not_const<auto (*)(int) noexcept -> void>();
        
        check_not_const<int bmltb::class_type::*>();
        check_not_const<auto (bmltb::class_type::*)() -> void>();
        check_not_const<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is volatile-qualified.
    {
        check_not_const<void volatile>();
        check_not_const<int volatile>();
        check_not_const<double volatile>();
        check_not_const<int volatile[]>();
        check_not_const<int volatile[3]>();
        check_not_const<int* volatile>();
        check_not_const<int volatile* volatile>();
        check_not_const<int(* volatile)[]>();
        
        check_not_const<bmltb::class_type volatile>();
        check_not_const<bmltb::enum_class volatile>();
        check_not_const<bmltb::union_type volatile>();
        check_not_const<bmltb::union_type volatile[]>();
        check_not_const<bmltb::incomplete_class volatile>();
        check_not_const<bmltb::incomplete_class* volatile[][2]>();
        
        check_not_const<bmltb::class_type* volatile>();
        check_not_const<bmltb::incomplete_class* volatile>();
        
        check_not_const<auto (* volatile)(int) noexcept -> void>();
        
        check_not_const<int bmltb::class_type::* volatile>();
        check_not_const<auto (bmltb::class_type::* volatile)() -> void>();
        check_not_const<auto (bmltb::class_type::* volatile)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input cannot be const-qualified.
    {
        check_not_const<int&>();
        check_not_const<int const&>();
        check_not_const<int&&>();
        check_not_const<int(&)[]>();
        check_not_const<int const(&)[]>();
        
        check_not_const<auto (int) -> void>();
        check_not_const<auto (int) const && noexcept -> void>();
        check_not_const<auto (&)(int) -> void>();
        check_not_const<auto (*&&)(int) noexcept -> void>();
        check_not_const<auto (* const&&)(int) noexcept -> void>();
    }

    return 0;
}
