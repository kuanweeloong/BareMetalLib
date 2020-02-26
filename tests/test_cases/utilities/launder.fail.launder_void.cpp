//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/launder.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when launder is invoked on a void pointer.
    {
        static_cast<void>(bml::launder(static_cast<void const*>(nullptr)));
    }

    return 0;
}
