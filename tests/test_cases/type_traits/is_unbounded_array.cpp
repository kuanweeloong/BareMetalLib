//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_unbounded_array.hpp>

template <typename T>
auto check_unbounded_array() noexcept -> void
{
    static_assert(bml::is_unbounded_array<T>::value);
    static_assert(bml::is_unbounded_array_v<T>);
}

template <typename T>
auto check_not_unbounded_array() noexcept -> void
{
    static_assert(!bml::is_unbounded_array<T>::value);
    static_assert(!bml::is_unbounded_array_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is an array of unknown bound.
    {
        check_unbounded_array<int[]>();
        check_unbounded_array<int const[]>();
        check_unbounded_array<int volatile[]>();
        check_unbounded_array<int const volatile[]>();
        
        check_unbounded_array<int[][2]>();
        check_unbounded_array<int const[][2]>();
        check_unbounded_array<int volatile[][2]>();
        check_unbounded_array<int const volatile[][2]>();
        
        check_unbounded_array<int[][2][3]>();
        check_unbounded_array<int const[][2][3]>();
        check_unbounded_array<int volatile[][2][3]>();
        check_unbounded_array<int const volatile[][2][3]>();
        
        check_unbounded_array<bmltb::class_type[][2][3]>();
        check_unbounded_array<bmltb::class_type const[][2][3]>();
        check_unbounded_array<bmltb::class_type volatile[][2][3]>();
        check_unbounded_array<bmltb::class_type const volatile[][2][3]>();
    }
    
    // Check that the result is false when the input type is not an array of unknown bound.
    {
        check_not_unbounded_array<int(*)[]>();
        check_not_unbounded_array<int const(*)[]>();
        check_not_unbounded_array<int volatile(*)[]>();
        check_not_unbounded_array<int const volatile(*)[]>();
        
        check_not_unbounded_array<int(&)[]>();
        check_not_unbounded_array<int const(&)[]>();
        check_not_unbounded_array<int volatile(&)[]>();
        check_not_unbounded_array<int const volatile(&)[]>();
        
        check_not_unbounded_array<int(&&)[]>();
        check_not_unbounded_array<int const(&&)[]>();
        check_not_unbounded_array<int volatile(&&)[]>();
        check_not_unbounded_array<int const volatile(&&)[]>();
        
        check_not_unbounded_array<int(*)[][2][3]>();
        check_not_unbounded_array<int const(*)[][2][3]>();
        check_not_unbounded_array<int volatile(*)[][2][3]>();
        check_not_unbounded_array<int const volatile(*)[][2][3]>();
        
        check_not_unbounded_array<int(&)[][2][3]>();
        check_not_unbounded_array<int const(&)[][2][3]>();
        check_not_unbounded_array<int volatile(&)[][2][3]>();
        check_not_unbounded_array<int const volatile(&)[][2][3]>();
        
        check_not_unbounded_array<int(&&)[][2][3]>();
        check_not_unbounded_array<int const(&&)[][2][3]>();
        check_not_unbounded_array<int volatile(&&)[][2][3]>();
        check_not_unbounded_array<int const volatile(&&)[][2][3]>();
        
        check_not_unbounded_array<void>();
        check_not_unbounded_array<void const>();
        check_not_unbounded_array<int>();
        check_not_unbounded_array<int const>();
        check_not_unbounded_array<int[3]>();
        check_not_unbounded_array<int volatile[3]>();
        check_not_unbounded_array<int*>();
        check_not_unbounded_array<int* const>();
        check_not_unbounded_array<int const volatile*>();
        
        check_not_unbounded_array<int&>();
        check_not_unbounded_array<int const volatile&>();
        check_not_unbounded_array<int&&>();
        check_not_unbounded_array<int const volatile&&>();
        
        check_not_unbounded_array<bmltb::class_type>();
        check_not_unbounded_array<bmltb::class_type const>();
        check_not_unbounded_array<bmltb::enum_class>();
        check_not_unbounded_array<bmltb::union_type>();
        check_not_unbounded_array<bmltb::union_type const volatile>();
        check_not_unbounded_array<bmltb::incomplete_class>();
        check_not_unbounded_array<int bmltb::class_type::*>();
        
        check_not_unbounded_array<auto (bmltb::class_type::*)() -> void>();
        check_not_unbounded_array<auto (bmltb::class_type::*)() & -> void>();
        check_not_unbounded_array<auto (bmltb::class_type::*)() && noexcept -> void>();
        check_not_unbounded_array<auto (bmltb::class_type::*)() const & -> void>();
        check_not_unbounded_array<
            auto (bmltb::class_type::*)() volatile && noexcept -> void>();
        
        check_not_unbounded_array<auto () -> void>();
        check_not_unbounded_array<auto (int) noexcept -> void>();
        check_not_unbounded_array<auto () & -> void>();
        check_not_unbounded_array<auto () & noexcept -> void>();
        check_not_unbounded_array<auto () const & -> void>();
        check_not_unbounded_array<auto () && -> void>();
        check_not_unbounded_array<auto () const && noexcept -> void>();
    }
    
    return 0;
}
