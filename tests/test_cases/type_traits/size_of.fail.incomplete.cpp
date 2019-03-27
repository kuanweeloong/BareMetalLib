//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/size_of.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when T is an incomplete type.
    {
        auto i = bml::size_of_v<int[]>();
    }

    return 0;
}
