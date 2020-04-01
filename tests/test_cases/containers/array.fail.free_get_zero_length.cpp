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
    // Check that a compile error occurs when a zero length array is provided to free get.
    {
        auto a = bml::array<int, 0>();
        static_cast<void>(bml::get<0>(a));
    }
    
    return 0;
}
