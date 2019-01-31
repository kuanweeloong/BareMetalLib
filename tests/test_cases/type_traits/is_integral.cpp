//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_integral.hpp>

template <typename T>
auto check_integral() noexcept -> void
{
    static_assert(bml::is_integral<T>::value);
    static_assert(bml::is_integral_v<T>);
    
    static_assert(bml::is_integral<T const>::value);
    static_assert(bml::is_integral_v<T const>);
    
    static_assert(bml::is_integral<T volatile>::value);
    static_assert(bml::is_integral_v<T volatile>);
    
    static_assert(bml::is_integral<T const volatile>::value);
    static_assert(bml::is_integral_v<T const volatile>);
}

template <typename T>
auto check_not_integral() noexcept -> void
{
    static_assert(!bml::is_integral<T>::value);
    static_assert(!bml::is_integral_v<T>);
    
    static_assert(!bml::is_integral<T const>::value);
    static_assert(!bml::is_integral_v<T const>);
    
    static_assert(!bml::is_integral<T volatile>::value);
    static_assert(!bml::is_integral_v<T volatile>);
    
    static_assert(!bml::is_integral<T const volatile>::value);
    static_assert(!bml::is_integral_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an integral type.
    {
        check_integral<bool>();
        check_integral<char>();
        check_integral<wchar_t>();
        check_integral<char16_t>();
        check_integral<char32_t>();
        check_integral<signed char>();
        check_integral<unsigned char>();
        check_integral<short>();
        check_integral<unsigned short>();
        check_integral<int>();
        check_integral<unsigned int>();
        check_integral<long>();
        check_integral<unsigned long>();
        check_integral<long long>();
        check_integral<unsigned long long>();
    }
    
    // Check that the result is false when the input is not an integral type.
    {
        check_not_integral<int*>();
        check_not_integral<int&>();
        check_not_integral<int const&>();
        check_not_integral<int&&>();
        check_not_integral<int volatile*>();
        check_not_integral<int[]>();
        check_not_integral<int[3]>();
        check_not_integral<int(&)[]>();
        check_not_integral<int[][2]>();
        
        check_not_integral<void>();
        check_not_integral<float>();
        check_not_integral<double>();
        check_not_integral<long double>();
        check_not_integral<float*>();
        check_not_integral<float const*>();
        check_not_integral<float&>();
        check_not_integral<float const volatile&>();
        check_not_integral<float&&>();
        check_not_integral<float volatile&&>();
        
        check_not_integral<bmltb::class_type>();
        check_not_integral<int bmltb::class_type::*>();
        check_not_integral<bmltb::union_type[]>();
        check_not_integral<bmltb::enum_class>();
        check_not_integral<bmltb::incomplete_class>();
        check_not_integral<bmltb::incomplete_class*[][2]>();
        
        check_not_integral<auto (int) -> void>();
        check_not_integral<auto (int) const && noexcept -> void>();
        check_not_integral<auto (&)(int) -> void>();
        check_not_integral<auto (*)(int) noexcept -> void>();
        check_not_integral<auto (*&&)(int) noexcept -> void>();
        check_not_integral<auto (bmltb::class_type::*)() -> void>();
        check_not_integral<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
