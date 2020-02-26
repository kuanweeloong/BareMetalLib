//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/move.hpp>
#include <bml/type_traits/is_same.hpp>

constexpr auto check_move_constexpr_func() noexcept -> bool
{
    auto x = int(42);
    auto const cx = int(420);
    
    return bml::move(x) == 42
        && bml::move(cx) == 420
        && bml::move(static_cast<int&&>(x)) == 42
        && bml::move(static_cast<int const&&>(cx)) == 420;
}

auto i = int(42);

auto get_num() noexcept -> int& { return i; };
auto get_num_c() noexcept -> int const& { return i; };
auto get_num_v() noexcept -> int volatile& { return i; };
auto get_num_cv() noexcept -> int const volatile& { return i; };

struct move_only
{
    inline static auto move_count = 0;
    
    move_only() = default;
    
    move_only(move_only const&) = delete;
    auto operator=(move_only const&) -> move_only& = delete;
    
    move_only(move_only&&) { ++move_count; };
    auto operator=(move_only&&) -> move_only& { ++move_count; return *this; };
};

auto receive(move_only) noexcept {};

auto test_main() noexcept -> int
{
    // Check that arguments are forwarded as xvalues.
    {
        // Lvalues
        auto x = int(42);
        auto const cx = int(42);
        auto volatile vx = int(42);
        auto const volatile cvx = int(42);
        
        static_assert(bml::is_same_v<decltype(bml::move(x)), int&&>);
        static_assert(bml::is_same_v<decltype(bml::move(cx)), int const&&>);
        static_assert(bml::is_same_v<decltype(bml::move(vx)), int volatile&&>);
        static_assert(bml::is_same_v<decltype(bml::move(cvx)), int const volatile&&>);
        
        // Rvalues
        static_assert(bml::is_same_v<decltype(bml::move(42)), int&&>);
        static_assert(bml::is_same_v<decltype(bml::move(get_num())), int&&>);
        static_assert(bml::is_same_v<decltype(bml::move(get_num_c())), int const&&>);
        static_assert(bml::is_same_v<decltype(bml::move(get_num_v())), int volatile&&>);
        static_assert(bml::is_same_v<decltype(bml::move(get_num_cv())), int const volatile&&>);
    }
    
    // Check that move can move move-only types.
    {
        auto m = move_only();
        bmltb_assert(move_only::move_count == 0);
        
        receive(bml::move(m));
        bmltb_assert(move_only::move_count == 1);
    }
    
    // Check that move is usable in a constexpr context.
    {
       constexpr auto i = 42;
       
       static_assert(bml::move(42) == 42);
       static_assert(bml::move(i) == 42);
       static_assert(check_move_constexpr_func());
    }

    return 0;
}
