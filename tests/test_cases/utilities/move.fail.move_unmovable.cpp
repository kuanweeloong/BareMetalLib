//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
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
