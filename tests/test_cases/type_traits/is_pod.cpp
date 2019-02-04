//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_pod.hpp>

template <typename T>
auto check_pod() noexcept -> void
{
    static_assert(bml::is_pod<T>::value);
    static_assert(bml::is_pod_v<T>);
    
    static_assert(bml::is_pod<T const>::value);
    static_assert(bml::is_pod_v<T const>);
    
    static_assert(bml::is_pod<T volatile>::value);
    static_assert(bml::is_pod_v<T volatile>);
    
    static_assert(bml::is_pod<T const volatile>::value);
    static_assert(bml::is_pod_v<T const volatile>);
}

template <typename T>
auto check_not_pod() noexcept -> void
{
    static_assert(!bml::is_pod<T>::value);
    static_assert(!bml::is_pod_v<T>);
    
    static_assert(!bml::is_pod<T const>::value);
    static_assert(!bml::is_pod_v<T const>);
    
    static_assert(!bml::is_pod<T volatile>::value);
    static_assert(!bml::is_pod_v<T volatile>);
    
    static_assert(!bml::is_pod<T const volatile>::value);
    static_assert(!bml::is_pod_v<T const volatile>);
}

struct trivial_class {};

struct non_trivial_class
{
    non_trivial_class();
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a POD type.
    {
        check_pod<int>();
        check_pod<double>();
        check_pod<int*>();
        check_pod<int const*>();
        check_pod<char[3]>();
        check_pod<char[]>();
        check_pod<char(*)[]>();
        
        check_pod<bmltb::enum_class>();
        check_pod<trivial_class>();
        check_pod<bmltb::union_type[]>();
        check_pod<int bmltb::class_type::*>();
        check_pod<bmltb::incomplete_class*>();
        check_pod<bmltb::incomplete_class*[][2]>();
        
        check_pod<auto (*)(int) noexcept -> void>();
        check_pod<auto (bmltb::class_type::*)() -> void>();
        check_pod<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input is not a POD type.
    {
        check_not_pod<int&>();
        check_not_pod<int const&>();
        check_not_pod<int&&>();
        check_not_pod<int(&)[]>();
        
        check_not_pod<non_trivial_class>();
        
        check_not_pod<auto (int) -> void>();
        check_not_pod<auto (int) const && noexcept -> void>();
        check_not_pod<auto (&)(int) -> void>();
        check_not_pod<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
