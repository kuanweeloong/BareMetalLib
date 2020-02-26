//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/variant.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when a variant is instantiated with an array alternative.
    {
        auto v = bml::variant<int, int[2]>(bml::in_place_index<0>, 42);
    }
    
    return 0;
}
