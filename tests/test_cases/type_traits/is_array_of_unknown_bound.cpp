//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_array_of_unknown_bound.hpp>

template <typename T>
auto check_array_of_unknown_bound() noexcept -> void
{
    static_assert(bml::is_array_of_unknown_bound<T>::value);
    static_assert(bml::is_array_of_unknown_bound_v<T>);
}

template <typename T>
auto check_not_array_of_unknown_bound() noexcept -> void
{
    static_assert(!bml::is_array_of_unknown_bound<T>::value);
    static_assert(!bml::is_array_of_unknown_bound_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is an array of unknown bound.
    {
        check_array_of_unknown_bound<int[]>();
        check_array_of_unknown_bound<int const[]>();
        check_array_of_unknown_bound<int volatile[]>();
        check_array_of_unknown_bound<int const volatile[]>();
        
        check_array_of_unknown_bound<int[][2]>();
        check_array_of_unknown_bound<int const[][2]>();
        check_array_of_unknown_bound<int volatile[][2]>();
        check_array_of_unknown_bound<int const volatile[][2]>();
        
        check_array_of_unknown_bound<int[][2][3]>();
        check_array_of_unknown_bound<int const[][2][3]>();
        check_array_of_unknown_bound<int volatile[][2][3]>();
        check_array_of_unknown_bound<int const volatile[][2][3]>();
        
        check_array_of_unknown_bound<bmltb::class_type[][2][3]>();
        check_array_of_unknown_bound<bmltb::class_type const[][2][3]>();
        check_array_of_unknown_bound<bmltb::class_type volatile[][2][3]>();
        check_array_of_unknown_bound<bmltb::class_type const volatile[][2][3]>();
    }
    
    // Check that the result is false when the input type is not an array of unknown bound.
    {
        check_not_array_of_unknown_bound<int(*)[]>();
        check_not_array_of_unknown_bound<int const(*)[]>();
        check_not_array_of_unknown_bound<int volatile(*)[]>();
        check_not_array_of_unknown_bound<int const volatile(*)[]>();
        
        check_not_array_of_unknown_bound<int(&)[]>();
        check_not_array_of_unknown_bound<int const(&)[]>();
        check_not_array_of_unknown_bound<int volatile(&)[]>();
        check_not_array_of_unknown_bound<int const volatile(&)[]>();
        
        check_not_array_of_unknown_bound<int(&&)[]>();
        check_not_array_of_unknown_bound<int const(&&)[]>();
        check_not_array_of_unknown_bound<int volatile(&&)[]>();
        check_not_array_of_unknown_bound<int const volatile(&&)[]>();
        
        check_not_array_of_unknown_bound<int(*)[][2][3]>();
        check_not_array_of_unknown_bound<int const(*)[][2][3]>();
        check_not_array_of_unknown_bound<int volatile(*)[][2][3]>();
        check_not_array_of_unknown_bound<int const volatile(*)[][2][3]>();
        
        check_not_array_of_unknown_bound<int(&)[][2][3]>();
        check_not_array_of_unknown_bound<int const(&)[][2][3]>();
        check_not_array_of_unknown_bound<int volatile(&)[][2][3]>();
        check_not_array_of_unknown_bound<int const volatile(&)[][2][3]>();
        
        check_not_array_of_unknown_bound<int(&&)[][2][3]>();
        check_not_array_of_unknown_bound<int const(&&)[][2][3]>();
        check_not_array_of_unknown_bound<int volatile(&&)[][2][3]>();
        check_not_array_of_unknown_bound<int const volatile(&&)[][2][3]>();
        
        check_not_array_of_unknown_bound<void>();
        check_not_array_of_unknown_bound<void const>();
        check_not_array_of_unknown_bound<int>();
        check_not_array_of_unknown_bound<int const>();
        check_not_array_of_unknown_bound<int[3]>();
        check_not_array_of_unknown_bound<int volatile[3]>();
        check_not_array_of_unknown_bound<int*>();
        check_not_array_of_unknown_bound<int* const>();
        check_not_array_of_unknown_bound<int const volatile*>();
        
        check_not_array_of_unknown_bound<int&>();
        check_not_array_of_unknown_bound<int const volatile&>();
        check_not_array_of_unknown_bound<int&&>();
        check_not_array_of_unknown_bound<int const volatile&&>();
        
        check_not_array_of_unknown_bound<bmltb::class_type>();
        check_not_array_of_unknown_bound<bmltb::class_type const>();
        check_not_array_of_unknown_bound<bmltb::enum_class>();
        check_not_array_of_unknown_bound<bmltb::union_type>();
        check_not_array_of_unknown_bound<bmltb::union_type const volatile>();
        check_not_array_of_unknown_bound<bmltb::incomplete_class>();
        check_not_array_of_unknown_bound<int bmltb::class_type::*>();
        
        check_not_array_of_unknown_bound<auto (bmltb::class_type::*)() -> void>();
        check_not_array_of_unknown_bound<auto (bmltb::class_type::*)() & -> void>();
        check_not_array_of_unknown_bound<auto (bmltb::class_type::*)() && noexcept -> void>();
        check_not_array_of_unknown_bound<auto (bmltb::class_type::*)() const & -> void>();
        check_not_array_of_unknown_bound<
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
        
        check_not_array_of_unknown_bound<auto () -> void>();
        check_not_array_of_unknown_bound<auto (int) noexcept -> void>();
        check_not_array_of_unknown_bound<auto () & -> void>();
        check_not_array_of_unknown_bound<auto () & noexcept -> void>();
        check_not_array_of_unknown_bound<auto () const & -> void>();
        check_not_array_of_unknown_bound<auto () && -> void>();
        check_not_array_of_unknown_bound<auto () const && noexcept -> void>();
    }
    
    return 0;
}
