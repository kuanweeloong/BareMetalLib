//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_base_of.hpp>

template <typename T, typename U>
auto check_base_of() noexcept -> void
{
    static_assert(bml::is_base_of<T, U>::value);
    static_assert(bml::is_base_of_v<T, U>);
    
    static_assert(bml::is_base_of<T const, U>::value);
    static_assert(bml::is_base_of_v<T const, U>);
    
    static_assert(bml::is_base_of<T, U const>::value);
    static_assert(bml::is_base_of_v<T, U const>);
    
    static_assert(bml::is_base_of<T const, U const>::value);
    static_assert(bml::is_base_of_v<T const, U const>);
    
    static_assert(bml::is_base_of<T volatile, U>::value);
    static_assert(bml::is_base_of_v<T volatile, U>);
    
    static_assert(bml::is_base_of<T, U volatile>::value);
    static_assert(bml::is_base_of_v<T, U volatile>);
    
    static_assert(bml::is_base_of<T volatile, U volatile>::value);
    static_assert(bml::is_base_of_v<T volatile, U volatile>);
    
    static_assert(bml::is_base_of<T const volatile, U>::value);
    static_assert(bml::is_base_of_v<T const volatile, U>);
    
    static_assert(bml::is_base_of<T, U const volatile>::value);
    static_assert(bml::is_base_of_v<T, U const volatile>);
    
    static_assert(bml::is_base_of<T const volatile, U const volatile>::value);
    static_assert(bml::is_base_of_v<T const volatile, U const volatile>);
}

template <typename T, typename U>
auto check_not_base_of() noexcept -> void
{
    static_assert(!bml::is_base_of<T, U>::value);
    static_assert(!bml::is_base_of_v<T, U>);
    
    static_assert(!bml::is_base_of<T const, U>::value);
    static_assert(!bml::is_base_of_v<T const, U>);
    
    static_assert(!bml::is_base_of<T, U const>::value);
    static_assert(!bml::is_base_of_v<T, U const>);
    
    static_assert(!bml::is_base_of<T const, U const>::value);
    static_assert(!bml::is_base_of_v<T const, U const>);
    
    static_assert(!bml::is_base_of<T volatile, U>::value);
    static_assert(!bml::is_base_of_v<T volatile, U>);
    
    static_assert(!bml::is_base_of<T, U volatile>::value);
    static_assert(!bml::is_base_of_v<T, U volatile>);
    
    static_assert(!bml::is_base_of<T volatile, U volatile>::value);
    static_assert(!bml::is_base_of_v<T volatile, U volatile>);
    
    static_assert(!bml::is_base_of<T const volatile, U>::value);
    static_assert(!bml::is_base_of_v<T const volatile, U>);
    
    static_assert(!bml::is_base_of<T, U const volatile>::value);
    static_assert(!bml::is_base_of_v<T, U const volatile>);
    
    static_assert(!bml::is_base_of<T const volatile, U const volatile>::value);
    static_assert(!bml::is_base_of_v<T const volatile, U const volatile>);
}

struct b {};
struct b1 : b {};
struct b2 : b {};
struct d : private b1, private b2 {};

auto test_main() noexcept -> int
{
    // Check that the result is true when the 2nd type is derived from the 1st type.
    {
        check_base_of<b, d>();
        check_base_of<b1, d>();
        check_base_of<b2, d>();
        check_base_of<b, b1>();
        check_base_of<b, b2>();
        check_base_of<b, b>();
    }
    
    // Check that the result is false when the 2nd type is not derived from the 1st type.
    {
        check_not_base_of<d, b>();
        check_not_base_of<bmltb::class_type, b>();
        
        check_not_base_of<b&, d>();
        check_not_base_of<b, d&>();
        check_not_base_of<b&, d&>();
        check_not_base_of<b&&, d>();
        check_not_base_of<b, d&&>();
        check_not_base_of<b&&, d&&>();
        
        check_not_base_of<d&, b&>();
        check_not_base_of<d&&, b&&>();
        
        check_not_base_of<b[3], d[3]>();
        check_not_base_of<d[3], b[3]>();
        check_not_base_of<b*, d*>();
        check_not_base_of<d*, b*>();
        
        check_not_base_of<bmltb::union_type, bmltb::union_type>();
        check_not_base_of<bmltb::union_type, bmltb::class_type>();
        check_not_base_of<bmltb::class_type, bmltb::union_type>();
        check_not_base_of<bmltb::class_type, bmltb::enum_class>();
        
        check_not_base_of<void, void>();
        check_not_base_of<int, int>();
        check_not_base_of<int, double>();
        check_not_base_of<double, int>();
    }

    return 0;
}
