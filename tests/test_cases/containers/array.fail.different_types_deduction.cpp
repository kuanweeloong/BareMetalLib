//
// Copyright (c) 2020 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/array.hpp>

struct a {};
struct b {};

auto test_main() noexcept -> int
{
    // Check that class template argument deduction fails when array's initializers are not of the
    // same type.
    {
        static_cast<void>(bml::array{a(), b()}));
    }
    
    return 0;
}
