//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/make_integer_sequence.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when N is negative.
    {
        using x = bml::make_integer_sequence<int, -1>;
    }
    
    return 0;
}
