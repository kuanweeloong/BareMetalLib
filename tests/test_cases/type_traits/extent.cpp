//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/extent.hpp>
#include <stddef.h>

template <typename T, ::size_t N, ::size_t Len>
auto check_extent() noexcept -> void
{
    static_assert(bml::extent<T, N>::value == Len);
    static_assert(bml::extent_v<T, N> == Len);
    
    static_assert(bml::extent<T const, N>::value == Len);
    static_assert(bml::extent_v<T const, N> == Len);
    
    static_assert(bml::extent<T volatile, N>::value == Len);
    static_assert(bml::extent_v<T volatile, N> == Len);
    
    static_assert(bml::extent<T const volatile, N>::value == Len);
    static_assert(bml::extent_v<T const volatile, N> == Len);
}

template <typename T, ::size_t Len>
auto check_extent_n_unspecified() noexcept -> void
{
    static_assert(bml::extent<T>::value == Len);
    static_assert(bml::extent_v<T> == Len);
    
    static_assert(bml::extent<T const>::value == Len);
    static_assert(bml::extent_v<T const> == Len);
    
    static_assert(bml::extent<T volatile>::value == Len);
    static_assert(bml::extent_v<T volatile> == Len);
    
    static_assert(bml::extent<T const volatile>::value == Len);
    static_assert(bml::extent_v<T const volatile> == Len);
}

auto test_main() noexcept -> int
{
    // Check that the result is equal to the number of elements along the dimension specified by N
    // if T is an array type with known bounds and N is smaller than the T's rank.
    {
        check_extent<int[3], 0, 3>();
        check_extent<int[3][2], 0, 3>();
        check_extent<int[3][2], 1, 2>();
        check_extent<int[3][2][5], 2, 5>();
        
        check_extent<bmltb::class_type[2], 0, 2>();
        check_extent<bmltb::class_type[2][3], 1, 3>();
        check_extent<bmltb::union_type[2], 0, 2>();
        
        check_extent<bmltb::incomplete_class[3], 0, 3>();
        check_extent<bmltb::incomplete_class[3][1], 0, 3>();
        check_extent<bmltb::incomplete_class*[1][2], 1, 2>();
    }
    
    // Check that the result is equal to the number of elements along the dimension specified by N
    // if T is an array of unknown bounds and N is both smaller than the T's rank and not 0 (i.e
    // does not specify the 1st dimension).
    {
        check_extent<int[][2], 1, 2>();
        check_extent<int[][2][5], 1, 2>();
        check_extent<int[][2][5], 2, 5>();
        
        check_extent<bmltb::class_type[][2], 1, 2>();
        check_extent<bmltb::union_type[][2][5], 2, 5>();
    }
    
    // Check that the result is 0 if T is an array of unknown bounds and N is 0 (i.e specifies the
    // 1st dimension).
    {
        check_extent<int[], 0, 0>();
        check_extent<int[][2], 0, 0>();
        check_extent<int[][2][5], 0, 0>();
        check_extent<int[][2][5], 0, 0>();
        
        check_extent<bmltb::class_type[][2], 0, 0>();
        check_extent<bmltb::union_type[][2][5], 0, 0>();
        check_extent<bmltb::incomplete_class[], 0, 0>();
    }
    
    // Check that the result is 0 if T is an array type and N is equal to or larger than the T's
    // rank.
    {
        check_extent<int[3], 1, 0>();
        check_extent<int[3], 10, 0>();
        check_extent<int[3][2], 2, 0>();
        check_extent<int[3][2], 10, 0>();
        check_extent<int[3][2][5], 10, 0>();
        
        check_extent<bmltb::class_type[2], 10, 0>();
        check_extent<bmltb::class_type[2][3], 2, 0>();
        check_extent<bmltb::class_type[2][3], 10, 0>();
        check_extent<bmltb::union_type[2], 10, 0>();
        
        check_extent<bmltb::incomplete_class[3], 10, 0>();
        check_extent<bmltb::incomplete_class[3][1], 2, 0>();
        check_extent<bmltb::incomplete_class[3][1], 10, 0>();
        check_extent<bmltb::incomplete_class*[1][2], 10, 0>();
        
        check_extent<int[], 1, 0>();
        check_extent<int[], 10, 0>();
        check_extent<int[][2], 10, 0>();
        check_extent<int[][2][5], 3, 0>();
        check_extent<int[][2][5], 10, 0>();
        
        check_extent<bmltb::class_type[][2], 10, 0>();
        check_extent<bmltb::union_type[][2][5], 10, 0>();
        check_extent<bmltb::incomplete_class[], 1, 0>();
        check_extent<bmltb::incomplete_class[], 10, 0>();
    }
    
    // Check that the result is equal to the number of elements along the 1st dimension if T is an
    // array type with known bounds and N is not specified.
    {
        check_extent_n_unspecified<int[3], 3>();
        check_extent_n_unspecified<int[3][2], 3>();
        check_extent_n_unspecified<int[3][2], 3>();
        check_extent_n_unspecified<int[3][2][5], 3>();
        
        check_extent_n_unspecified<bmltb::class_type[2], 2>();
        check_extent_n_unspecified<bmltb::class_type[2][3], 2>();
        check_extent_n_unspecified<bmltb::union_type[2], 2>();
        
        check_extent_n_unspecified<bmltb::incomplete_class[3], 3>();
        check_extent_n_unspecified<bmltb::incomplete_class[3][1], 3>();
        check_extent_n_unspecified<bmltb::incomplete_class*[1][2], 1>();
    }
    
    // Check that the result is 0 if T is an array of unknown bounds and N is not specified.
    {
        check_extent_n_unspecified<int[], 0>();
        check_extent_n_unspecified<int[][2], 0>();
        check_extent_n_unspecified<int[][2][5], 0>();
        check_extent_n_unspecified<int[][2][5], 0>();
        
        check_extent_n_unspecified<bmltb::class_type[][2], 0>();
        check_extent_n_unspecified<bmltb::union_type[][2][5], 0>();
        check_extent_n_unspecified<bmltb::incomplete_class[], 0>();
    }
    
    // Check that the result is 0 if the T is not an array type, no matter the value of N.
    {
        // N == 0
        check_extent<void, 0, 0>();
        check_extent<bool, 0, 0>();
        check_extent<int, 0, 0>();
        check_extent<int, 0, 0>();
        check_extent<int*, 0, 0>();
        check_extent<int const*, 0, 0>();
        check_extent<int&, 0, 0>();
        check_extent<int const&, 0, 0>();
        check_extent<int&&, 0, 0>();
        check_extent<int(&)[], 0, 0>();
        check_extent<int(*)[], 0, 0>();
        check_extent<int(&)[][3], 0, 0>();
        check_extent<int(*)[][3], 0, 0>();
        check_extent<int(&)[][3][2], 0, 0>();
        check_extent<int(*)[][3][2], 0, 0>();
        check_extent<double, 0, 0>();
        check_extent<char, 0, 0>();
        
        check_extent<bmltb::enum_class, 0, 0>();
        check_extent<bmltb::class_type, 0, 0>();
        check_extent<bmltb::union_type, 0, 0>();
        check_extent<bmltb::incomplete_class, 0, 0>();
        check_extent<int bmltb::class_type::*, 0, 0>();
        check_extent<bmltb::incomplete_class*, 0, 0>();
        
        check_extent<bmltb::class_type(*)[2][3], 0, 0>();
        check_extent<bmltb::union_type(&)[][2][5], 0, 0>();
        check_extent<bmltb::incomplete_class(*&&)[3], 0, 0>();
        
        check_extent<auto (*)(int) noexcept -> void, 0, 0>();
        check_extent<auto (bmltb::class_type::*)() -> void, 0, 0>();
        check_extent<auto (bmltb::class_type::*)() const volatile && noexcept -> void, 0, 0>();
        
        check_extent<auto (...) noexcept -> void, 0, 0>();
        check_extent<auto (char, double) const && noexcept -> int, 0, 0>();
        check_extent<auto (*&&)(int) noexcept -> void, 0, 0>();
        
        // N == random assortment of numbers
        check_extent<void, 5, 0>();
        check_extent<bool, 8, 0>();
        check_extent<int, 1, 0>();
        check_extent<int, 3, 0>();
        check_extent<int*, 12, 0>();
        check_extent<int const*, 9, 0>();
        check_extent<int&, 9, 0>();
        check_extent<int const&, 40, 0>();
        check_extent<int&&, 21, 0>();
        check_extent<int(&)[], 3, 0>();
        check_extent<int(*)[], 120, 0>();
        check_extent<int(&)[][3], 255, 0>();
        check_extent<int(*)[][3], 8, 0>();
        check_extent<int(&)[][3][2], 2, 0>();
        check_extent<int(*)[][3][2], 100, 0>();
        check_extent<double, 43, 0>();
        check_extent<char, 43, 0>();
        
        check_extent<bmltb::enum_class, 1, 0>();
        check_extent<bmltb::class_type, 2, 0>();
        check_extent<bmltb::union_type, 10, 0>();
        check_extent<bmltb::incomplete_class, 21, 0>();
        check_extent<int bmltb::class_type::*, 35, 0>();
        check_extent<bmltb::incomplete_class*, 1, 0>();
        
        check_extent<bmltb::class_type(*)[2][3], 4, 0>();
        check_extent<bmltb::union_type(&)[][2][5], 5, 0>();
        check_extent<bmltb::incomplete_class(*&&)[3], 1, 0>();
        
        check_extent<auto (*)(int) noexcept -> void, 3, 0>();
        check_extent<auto (bmltb::class_type::*)() -> void, 4, 0>();
        check_extent<auto (bmltb::class_type::*)() const volatile && noexcept -> void, 8, 0>();
        
        check_extent<auto (...) noexcept -> void, 92, 0>();
        check_extent<auto (char, double) const && noexcept -> int, 2356, 0>();
        check_extent<auto (*&&)(int) noexcept -> void, 19327, 0>();
    }
    
    // Check that the result is 0 if the T is not an array type and N is not specified.
    {
        check_extent_n_unspecified<void, 0>();
        check_extent_n_unspecified<bool, 0>();
        check_extent_n_unspecified<int, 0>();
        check_extent_n_unspecified<int*, 0>();
        check_extent_n_unspecified<int const*, 0>();
        check_extent_n_unspecified<int&, 0>();
        check_extent_n_unspecified<int const&, 0>();
        check_extent_n_unspecified<int&&, 0>();
        check_extent_n_unspecified<int(&)[], 0>();
        check_extent_n_unspecified<int(*)[], 0>();
        check_extent_n_unspecified<int(&)[][3], 0>();
        check_extent_n_unspecified<int(*)[][3], 0>();
        check_extent_n_unspecified<int(&)[][3][2], 0>();
        check_extent_n_unspecified<int(*)[][3][2], 0>();
        check_extent_n_unspecified<double, 0>();
        check_extent_n_unspecified<char, 0>();
        
        check_extent_n_unspecified<bmltb::enum_class, 0>();
        check_extent_n_unspecified<bmltb::class_type, 0>();
        check_extent_n_unspecified<bmltb::union_type, 0>();
        check_extent_n_unspecified<bmltb::incomplete_class, 0>();
        check_extent_n_unspecified<int bmltb::class_type::*, 0>();
        check_extent_n_unspecified<bmltb::incomplete_class*, 0>();
        
        check_extent_n_unspecified<bmltb::class_type(*)[2][3], 0>();
        check_extent_n_unspecified<bmltb::union_type(&)[][2][5], 0>();
        check_extent_n_unspecified<bmltb::incomplete_class(*&&)[3], 0>();
        
        check_extent_n_unspecified<auto (*)(int) noexcept -> void, 0>();
        check_extent_n_unspecified<auto (bmltb::class_type::*)() -> void, 0>();
        check_extent_n_unspecified<
            auto (bmltb::class_type::*)() const volatile && noexcept -> void, 0>();
        
        check_extent_n_unspecified<auto (...) noexcept -> void, 0>();
        check_extent_n_unspecified<auto (char, double) const && noexcept -> int, 0>();
        check_extent_n_unspecified<auto (*&&)(int) noexcept -> void, 0>();
    }

    return 0;
}
