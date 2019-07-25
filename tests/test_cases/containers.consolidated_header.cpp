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
#include <bml/containers.hpp>

auto test_main() noexcept -> int
{
    // Check that in_place is available.
    {
        static_assert(sizeof(bml::in_place) > 0);
    }
    
    // Check that in_place_index is available.
    {
        static_assert(sizeof(bml::in_place_index<2>) > 0);
    }
    
    // Check that optional is available.
    {
        static_assert(sizeof(bml::optional<int>) > 0);
    }
    
    // Check that tuple is available.
    {
        static_assert(sizeof(bml::tuple<int, char>) > 0);
    }
    
    // Check that variant is available.
    {
        static_assert(sizeof(bml::variant<int, char>) > 0);
    }
    
    return 0;
}
