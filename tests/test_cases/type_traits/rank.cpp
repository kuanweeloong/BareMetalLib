//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/rank.hpp>
#include <stddef.h>

template <typename T, ::size_t N>
auto check_rank() noexcept -> void
{
    static_assert(bml::rank<T>::value == N);
    static_assert(bml::rank_v<T> == N);
    
    static_assert(bml::rank<T const>::value == N);
    static_assert(bml::rank_v<T const> == N);
    
    static_assert(bml::rank<T volatile>::value == N);
    static_assert(bml::rank_v<T volatile> == N);
    
    static_assert(bml::rank<T const volatile>::value == N);
    static_assert(bml::rank_v<T const volatile> == N);
}

auto test_main() noexcept -> int
{
    // Check that the result is equal to the number of dimensions in the input type if the input is
    // an array type.
    {
        check_rank<int[], 1>();
        check_rank<int[3], 1>();
        check_rank<int[][2], 2>();
        check_rank<int[3][2], 2>();
        check_rank<int[][2][5], 3>();
        check_rank<int[3][2][5], 3>();
        
        check_rank<bmltb::class_type[2], 1>();
        check_rank<bmltb::class_type[2][3], 2>();
        check_rank<bmltb::union_type[2], 1>();
        check_rank<bmltb::union_type[][2][5], 3>();
        check_rank<bmltb::incomplete_class[], 1>();
        check_rank<bmltb::incomplete_class[3], 1>();
        check_rank<bmltb::incomplete_class[3][1], 2>();
        check_rank<bmltb::incomplete_class*[1][2], 2>();
    }
    
    // Check that the result is equal to 0 if the input type is not an array type.
    {
        check_rank<void, 0>();
        check_rank<bool, 0>();
        check_rank<int, 0>();
        check_rank<int*, 0>();
        check_rank<int const*, 0>();
        check_rank<int&, 0>();
        check_rank<int const&, 0>();
        check_rank<int&&, 0>();
        check_rank<int(&)[], 0>();
        check_rank<int(*)[], 0>();
        check_rank<int(&)[][3], 0>();
        check_rank<int(*)[][3], 0>();
        check_rank<int(&)[][3][2], 0>();
        check_rank<int(*)[][3][2], 0>();
        check_rank<double, 0>();
        check_rank<char, 0>();
        
        check_rank<bmltb::enum_class, 0>();
        check_rank<bmltb::class_type, 0>();
        check_rank<bmltb::union_type, 0>();
        check_rank<bmltb::incomplete_class, 0>();
        check_rank<int bmltb::class_type::*, 0>();
        check_rank<bmltb::incomplete_class*, 0>();
        
        check_rank<bmltb::class_type(*)[2][3], 0>();
        check_rank<bmltb::union_type(&)[][2][5], 0>();
        check_rank<bmltb::incomplete_class(*&&)[3], 0>();
        
        check_rank<auto (*)(int) noexcept -> void, 0>();
        check_rank<auto (bmltb::class_type::*)() -> void, 0>();
        check_rank<auto (bmltb::class_type::*)() const volatile && noexcept -> void, 0>();
        
        check_rank<auto (...) noexcept -> void, 0>();
        check_rank<auto (char, double) const && noexcept -> int, 0>();
        check_rank<auto (*&&)(int) noexcept -> void, 0>();
    }

    return 0;
}
