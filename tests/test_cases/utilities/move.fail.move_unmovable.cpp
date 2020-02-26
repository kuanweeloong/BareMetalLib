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

struct no_move
{
    no_move() = default;
    
    no_move(no_move const&) = delete;
    no_move(no_move&&) = delete;
    
    auto operator=(no_move const&) -> no_move& = delete;
    auto operator=(no_move&&) -> no_move& = delete;
};

auto receive(no_move) noexcept {}

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when move is invoked on an unmovable type.
    {
        auto m = no_move();
        
        receive(bml::move(m));
    }

    return 0;
}
