//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
