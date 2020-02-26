//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/void_ty.hpp>
#include <bml/type_traits/is_same.hpp>

template <typename... Ts>
auto check_void() noexcept -> void
{
    static_assert(bml::is_same_v<bml::void_ty<Ts...>, void>);
}

auto test_main() noexcept -> int
{
    // Check that void_ty always names void regardless of the input types.
    {
        check_void<>();

        check_void<void>();
        check_void<void, void>();
        check_void<void, void, void>();
        check_void<void, void, void, void>();

        check_void<void const>();
        check_void<void const, void volatile>();
        check_void<void*, void const*, void const volatile*>();

        check_void<int&&, int const&, int[3], double, char>();
        check_void<bmltb::class_type, bmltb::enum_class, bmltb::union_type>();
        check_void<bmltb::class_type const, bmltb::enum_class*, bmltb::union_type volatile>();
        check_void<bmltb::incomplete_class>();
        check_void<bmltb::incomplete_class*, bmltb::incomplete_class[]>();

        check_void<auto (int) -> void, auto (int) const && noexcept -> double>();

        check_void<bml::void_ty<>>();
        check_void<bml::void_ty<>, bml::void_ty<void>>();
        check_void<bml::void_ty<>, bml::void_ty<void>, bml::void_ty<>>();
    }

    return 0;
}
