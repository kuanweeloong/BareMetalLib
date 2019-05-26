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
