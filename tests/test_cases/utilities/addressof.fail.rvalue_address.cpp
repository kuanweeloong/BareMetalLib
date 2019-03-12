//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/utilities/addressof.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when addressof is invoked on an rvalue.
    {
        auto p = bml::addressof(42);
    }

    return 0;
}
