//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/utilities/launder.hpp>

auto foo() noexcept -> void {};

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when launder is invoked on a function pointer.
    {
        static_cast<void>(bml::launder(foo));
    }

    return 0;
}
