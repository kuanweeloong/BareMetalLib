//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/tuple.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when an invalid index is passed to free get.
    {
        auto t = bml::tuple<int, double>(42, 200.5);
        auto val = bml::get<3>(t);
    }
    
    return 0;
}
