//
// Copyright (c) 2020 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/array.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when a negative length array is instantiated.
    {
        static_cast<void>(bml::array<int, -10>());
    }
    
    return 0;
}
