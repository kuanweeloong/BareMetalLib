//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/extent.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when N is negative.
    {
        auto i = bml::extent_v<int[5], -1>;
    }

    return 0;
}
