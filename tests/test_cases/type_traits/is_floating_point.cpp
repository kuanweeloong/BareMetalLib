//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_floating_point.hpp>

template <typename T>
auto check_floating_point() noexcept -> void
{
    static_assert(bml::is_floating_point<T>::value);
    static_assert(bml::is_floating_point_v<T>);
    
    static_assert(bml::is_floating_point<T const>::value);
    static_assert(bml::is_floating_point_v<T const>);
    
    static_assert(bml::is_floating_point<T volatile>::value);
    static_assert(bml::is_floating_point_v<T volatile>);
    
    static_assert(bml::is_floating_point<T const volatile>::value);
    static_assert(bml::is_floating_point_v<T const volatile>);
}

template <typename T>
auto check_not_floating_point() noexcept -> void
{
    static_assert(!bml::is_floating_point<T>::value);
    static_assert(!bml::is_floating_point_v<T>);
    
    static_assert(!bml::is_floating_point<T const>::value);
    static_assert(!bml::is_floating_point_v<T const>);
    
    static_assert(!bml::is_floating_point<T volatile>::value);
    static_assert(!bml::is_floating_point_v<T volatile>);
    
    static_assert(!bml::is_floating_point<T const volatile>::value);
    static_assert(!bml::is_floating_point_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a floating point type.
    {
        check_floating_point<float>();
        check_floating_point<double>();
        check_floating_point<long double>();
    }
    
    // Check that the result is false when the input is not a floating point type.
    {
        check_not_floating_point<float*>();
        check_not_floating_point<float&>();
        check_not_floating_point<float const&>();
        check_not_floating_point<float&&>();
        check_not_floating_point<float volatile*>();
        check_not_floating_point<float[]>();
        check_not_floating_point<float[3]>();
        check_not_floating_point<float(&)[]>();
        check_not_floating_point<float[][2]>();
        
        check_not_floating_point<bool>();
        check_not_floating_point<char>();
        check_not_floating_point<wchar_t>();
        check_not_floating_point<char16_t>();
        check_not_floating_point<char32_t>();
        check_not_floating_point<signed char>();
        check_not_floating_point<unsigned char>();
        check_not_floating_point<short>();
        check_not_floating_point<unsigned short>();
        check_not_floating_point<int>();
        check_not_floating_point<unsigned int>();
        check_not_floating_point<long>();
        check_not_floating_point<unsigned long>();
        check_not_floating_point<long long>();
        check_not_floating_point<unsigned long long>();
        check_not_floating_point<int*>();
        check_not_floating_point<int const*>();
        check_not_floating_point<int&>();
        check_not_floating_point<int const volatile&>();
        check_not_floating_point<int&&>();
        check_not_floating_point<int volatile&&>();
        
        check_not_floating_point<void>();
        check_not_floating_point<bmltb::class_type>();
        check_not_floating_point<int bmltb::class_type::*>();
        check_not_floating_point<bmltb::union_type[]>();
        check_not_floating_point<bmltb::enum_class>();
        check_not_floating_point<bmltb::incomplete_class>();
        check_not_floating_point<bmltb::incomplete_class*[][2]>();
        
        check_not_floating_point<auto (int) -> void>();
        check_not_floating_point<auto (int) const && noexcept -> void>();
        check_not_floating_point<auto (&)(int) -> void>();
        check_not_floating_point<auto (*)(int) noexcept -> void>();
        check_not_floating_point<auto (*&&)(int) noexcept -> void>();
        check_not_floating_point<auto (bmltb::class_type::*)() -> void>();
        check_not_floating_point<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
