//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/utilities/integer_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when integer_sequence is instantiated with a non-integral
    // type.
    {
        auto x = bml::integer_sequence<double>();
    }

    return 0;
}
