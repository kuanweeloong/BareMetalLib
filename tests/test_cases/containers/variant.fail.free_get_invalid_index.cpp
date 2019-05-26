//
// Copyright (c) 2019 Wee Loong Kuan
//
// BareMetalLib is based on libc++ (https://libcxx.llvm.org/).
// 
// This file is licensed under under the Apache License v2.0 with LLVM Exceptions. For more details,
// see the LICENSE.md file in the top-level directory of this distribution, or copy at 
// https://llvm.org/LICENSE.txt.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/variant.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when an invalid index is passed to free get.
    {
        auto v = bml::variant<int, double>(bml::in_place_index<0>, 42);
        auto val = bml::get<3>(v);
    }
    
    return 0;
}
