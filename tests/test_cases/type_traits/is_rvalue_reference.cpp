//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_rvalue_reference.hpp>

template <typename T>
auto check_rvalue_reference() noexcept -> void
{
    static_assert(bml::is_rvalue_reference<T>::value);
    static_assert(bml::is_rvalue_reference_v<T>);
    
    static_assert(bml::is_rvalue_reference<T const>::value);
    static_assert(bml::is_rvalue_reference_v<T const>);
    
    static_assert(bml::is_rvalue_reference<T volatile>::value);
    static_assert(bml::is_rvalue_reference_v<T volatile>);
    
    static_assert(bml::is_rvalue_reference<T const volatile>::value);
    static_assert(bml::is_rvalue_reference_v<T const volatile>);
}

template <typename T>
auto check_not_rvalue_reference() noexcept -> void
{
    static_assert(!bml::is_rvalue_reference<T>::value);
    static_assert(!bml::is_rvalue_reference_v<T>);
    
    static_assert(!bml::is_rvalue_reference<T const>::value);
    static_assert(!bml::is_rvalue_reference_v<T const>);
    
    static_assert(!bml::is_rvalue_reference<T volatile>::value);
    static_assert(!bml::is_rvalue_reference_v<T volatile>);
    
    static_assert(!bml::is_rvalue_reference<T const volatile>::value);
    static_assert(!bml::is_rvalue_reference_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a rvalue reference.
    {
        check_rvalue_reference<int&&>();
        check_rvalue_reference<int const&&>();
        check_rvalue_reference<int(&&)[]>();
        check_rvalue_reference<bmltb::class_type&&>();
        check_rvalue_reference<auto (&&)(int) -> void>();
    }
    
    // Check that the result is false when the input is not a rvalue reference.
    {
        check_not_rvalue_reference<void>();
        check_not_rvalue_reference<int>();
        check_not_rvalue_reference<double>();
        check_not_rvalue_reference<int*>();
        check_not_rvalue_reference<int const*>();
        check_not_rvalue_reference<char[3]>();
        check_not_rvalue_reference<char[]>();
        check_not_rvalue_reference<char(*)[]>();
        check_not_rvalue_reference<int&>();
        check_not_rvalue_reference<int const&>();
        
        check_not_rvalue_reference<bmltb::class_type>();
        check_not_rvalue_reference<int bmltb::class_type::*>();
        check_not_rvalue_reference<bmltb::enum_class>();
        check_not_rvalue_reference<bmltb::union_type[]>();
        check_not_rvalue_reference<bmltb::incomplete_class>();
        check_not_rvalue_reference<bmltb::incomplete_class*>();
        check_not_rvalue_reference<bmltb::incomplete_class*[][2]>();
        
        check_not_rvalue_reference<auto (int) -> void>();
        check_not_rvalue_reference<auto (int) const && noexcept -> void>();
        check_not_rvalue_reference<auto (*)(int) noexcept -> void>();
        check_not_rvalue_reference<auto (*&)(int) noexcept -> void>();
        check_not_rvalue_reference<auto (bmltb::class_type::*)() -> void>();
        check_not_rvalue_reference<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
