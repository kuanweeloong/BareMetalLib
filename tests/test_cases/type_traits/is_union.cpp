//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_union.hpp>

template <typename T>
auto check_union() noexcept -> void
{
    static_assert(bml::is_union<T>::value);
    static_assert(bml::is_union_v<T>);
    
    static_assert(bml::is_union<T const>::value);
    static_assert(bml::is_union_v<T const>);
    
    static_assert(bml::is_union<T volatile>::value);
    static_assert(bml::is_union_v<T volatile>);
    
    static_assert(bml::is_union<T const volatile>::value);
    static_assert(bml::is_union_v<T const volatile>);
}

template <typename T>
auto check_not_union() noexcept -> void
{
    static_assert(!bml::is_union<T>::value);
    static_assert(!bml::is_union_v<T>);
    
    static_assert(!bml::is_union<T const>::value);
    static_assert(!bml::is_union_v<T const>);
    
    static_assert(!bml::is_union<T volatile>::value);
    static_assert(!bml::is_union_v<T volatile>);
    
    static_assert(!bml::is_union<T const volatile>::value);
    static_assert(!bml::is_union_v<T const volatile>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is a union type.
    {
        check_union<bmltb::union_type>();
    }
    
    // Check that the result is false when the input is not a union type.
    {
        check_not_union<bmltb::union_type*>();
        check_not_union<bmltb::union_type&>();
        check_not_union<bmltb::union_type const&>();
        check_not_union<bmltb::union_type&&>();
        check_not_union<bmltb::union_type volatile*>();
        check_not_union<bmltb::union_type(&)[]>();
        check_not_union<bmltb::union_type(*)[]>();
        check_not_union<bmltb::union_type[]>();
        check_not_union<bmltb::union_type[3]>();
        check_not_union<bmltb::union_type[][2]>();
        
        check_not_union<int>();
        check_not_union<double>();
        check_not_union<int*>();
        check_not_union<int const*>();
        check_not_union<char[3]>();
        check_not_union<char[]>();
        check_not_union<char(*)[]>();
        check_not_union<int&>();
        check_not_union<int const&>();
        check_not_union<int&&>();
        check_not_union<int(&)[]>();
        
        check_not_union<bmltb::class_type>();
        check_not_union<int bmltb::class_type::*>();
        check_not_union<bmltb::enum_class>();
        check_not_union<bmltb::incomplete_class*>();
        check_not_union<bmltb::incomplete_class*[][2]>();
        
        check_not_union<auto (int) -> void>();
        check_not_union<auto (int) const && noexcept -> void>();
        check_not_union<auto (*)(int) noexcept -> void>();
        check_not_union<auto (&)(int) -> void>();
        check_not_union<auto (*&&)(int) noexcept -> void>();
        check_not_union<auto (bmltb::class_type::*)() -> void>();
        check_not_union<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
    }

    return 0;
}
