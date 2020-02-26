//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <stddef.h>
#include <bml_testbench.hpp>
#include <bml/type_traits/type_pack_element.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/integral_constant.hpp>
#include <bml/type_traits/is_detected.hpp>

template <typename Expected, ::ptrdiff_t N, typename... Ts>
auto check_result() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::type_pack_element<N, Ts...>::type, Expected>);
    static_assert(bml::is_same_v<bml::type_pack_element_ty<N, Ts...>, Expected>);
}

template <typename T>
using type_member_alias = typename T::type;

template <typename PtrDiffConstant>
using valid_type_pack_element_ty_empty_pack = bml::type_pack_element_ty<PtrDiffConstant::value>;

template <typename PtrDiffConstant, typename... Ts>
using valid_type_pack_element_ty_n_too_large =
    bml::type_pack_element_ty<PtrDiffConstant::value, Ts...>;

auto test_main() noexcept -> int
{
    // Check that the result names the N-th type in the type pack when the pack has at least one
    // type.
    {
        check_result<void, 0, void>();
        check_result<int, 0, int>();
        check_result<int, 0, int, char, double>();
        
        check_result<int const, 1, void*, int const, double, bmltb::union_type>();
        check_result<int[], 1, int, int[], double, bmltb::union_type>();
        check_result<bmltb::class_type&&, 1, int, bmltb::class_type&&, double, int>();
        
        check_result<char**, 2, int, char, char**>();
        check_result<double, 2, int, char, double, int>();
        check_result<void const volatile, 2, int, bmltb::class_type, void const volatile, int>();
    }
    
    // Check that there is no "type" member type alias when the type pack is empty.
    {
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<0>>);
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<5>>);
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<10>>);
        
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_empty_pack,
            bml::integral_constant<::ptrdiff_t, 0>>);
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_empty_pack,
            bml::integral_constant<::ptrdiff_t, 5>>);
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_empty_pack,
            bml::integral_constant<::ptrdiff_t, 10>>);
    }
    
    // Check that there is no "type" member type alias when N is larger than or equal to the length
    // of the type pack.
    {
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<1, int>>);
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<5, int>>);
        static_assert(!bml::is_detected_v<type_member_alias, bml::type_pack_element<10, int, int>>);
        
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_n_too_large,
            bml::integral_constant<::ptrdiff_t, 1>, int>);
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_n_too_large,
            bml::integral_constant<::ptrdiff_t, 5>, int>);
        static_assert(!bml::is_detected_v<valid_type_pack_element_ty_n_too_large,
            bml::integral_constant<::ptrdiff_t, 10>, int, int>);
    }
    
    // Check that type_pack_element is default constructible even when there is no "type" member
    // type alias.
    {
        auto empty_pack = bml::type_pack_element<1>();
        auto n_too_large = bml::type_pack_element<1, int>();
        
        static_cast<void>(empty_pack);
        static_cast<void>(n_too_large);
    }
    
    return 0;
}
