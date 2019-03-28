//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/aligned_union.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when Len is negative.
    {
        using T = typename bml::aligned_union<-2, int, double>::type;
    }

    return 0;
}
