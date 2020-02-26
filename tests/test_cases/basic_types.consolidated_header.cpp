//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/basic_types.hpp>

auto test_main() noexcept -> int
{
    // Check that nullptr_ty is available.
    {
        static_assert([](bml::nullptr_ty)
        {
            return true;
        }(nullptr));
    }
    
    return 0;
}
