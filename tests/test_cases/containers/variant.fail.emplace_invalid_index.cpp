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
    // Check that a compile error occurs when an invalid index is used to emplace an alternative.
    {
        auto v = bml::variant<int, double>(bml::in_place_index<0>, 42);
        v.emplace<3>(100);
    }
    
    return 0;
}
