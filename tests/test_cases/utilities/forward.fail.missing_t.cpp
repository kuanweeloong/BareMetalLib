//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/utilities/forward.hpp>

struct arg {};

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when forward is invoked without specifying T.
    {
        auto a = arg();
        
        static_cast<void>(bml::forward(a));
    }

    return 0;
}
