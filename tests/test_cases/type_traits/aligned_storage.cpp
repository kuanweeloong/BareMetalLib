//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <stddef.h>
#include <bml/type_traits/aligned_storage.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_trivial.hpp>
#include <bml/type_traits/is_standard_layout.hpp>

template <::size_t Len, ::size_t Align>
auto check_result() noexcept -> void
{
    using T = typename bml::aligned_storage<Len, Align>::type;
    
    static_assert(bml::is_same_v<bml::aligned_storage_ty<Len, Align>, T>);
    static_assert(bml::is_trivial_v<T>);
    static_assert(bml::is_standard_layout_v<T>);
    static_assert(alignof(T) == Align);
    static_assert(sizeof(T) >= Len);
}

template <::size_t Len>
auto check_result_default() noexcept -> void
{
    using T = typename bml::aligned_storage<Len>::type;
    
    static_assert(bml::is_same_v<bml::aligned_storage_ty<Len>, T>);
    static_assert(bml::is_trivial_v<T>);
    static_assert(bml::is_standard_layout_v<T>);
    static_assert(alignof(T) == alignof(::max_align_t));
    static_assert(sizeof(T) >= Len);
}

auto test_main() noexcept -> int
{
    // Check that the size of the result is at least Len bytes and that its alignment is equal to
    // the input alignment.
    {
        check_result<10, 1>();
        check_result<10, 4>();
        check_result<10, 8>();
        check_result<10, 16>();
        check_result<10, 32>();
        check_result<12, 16>();
        check_result<20, 32>();
        check_result<40, 32>();
    }
    
    // Check that the size of the result is at least Len bytes and that its alignment is equal to
    // the alignment of ::max_align_t when no input alignment is specified.
    {
        check_result_default<1>();
        check_result_default<2>();
        check_result_default<3>();
        check_result_default<4>();
        check_result_default<5>();
        check_result_default<7>();
        check_result_default<8>();
        check_result_default<9>();
        check_result_default<10>();
        check_result_default<15>();
        check_result_default<16>();
        check_result_default<17>();
        check_result_default<20>();
        check_result_default<40>();
    }
    
    return 0;
}
