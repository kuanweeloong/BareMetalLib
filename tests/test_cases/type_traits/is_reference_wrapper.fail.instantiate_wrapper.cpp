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
#include <bml/type_traits/is_reference_wrapper.hpp>

auto test_main() noexcept -> int
{
    // Check that is_reference_wrapper has no dependency on the actual reference_wrapper header by
    // checking that a compile error occurs when trying to instantate reference_wrapper without
    // including the reference_wrapper header.
    {
        auto i = 0;
        static_cast<void>(bml::reference_wrapper<int>(i));
    }
    
    return 0;
}
