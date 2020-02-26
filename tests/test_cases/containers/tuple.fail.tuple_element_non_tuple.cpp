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
    // Check that tuple_element is not defined when T is not a tuple.
    {
        static_cast<void>(sizeof(bml::tuple_element<0, bmltb::class_type>));
    }
    
    return 0;
}
