//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/optional.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when a optional is instantiated with reference types.
    {
        auto i = 42;
        auto v = bml::optional<int const&>(bml::in_place, i);
    }
    
    return 0;
}
