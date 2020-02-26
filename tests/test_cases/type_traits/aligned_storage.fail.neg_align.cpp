//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/aligned_storage.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when Align is negative.
    {
        using T = typename bml::aligned_storage<8, -2>::type;
    }

    return 0;
}
