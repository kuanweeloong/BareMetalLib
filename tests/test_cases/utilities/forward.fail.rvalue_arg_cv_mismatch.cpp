//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/forward.hpp>

struct arg {};
auto get_arg_cv() noexcept -> arg const volatile { return arg(); };

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when forward is invoked with a cv-qualified rvalue argument
    // and T does not have the same level of cv-qualification.
    {
        static_cast<void>(bml::forward<arg const&>(get_arg_cv()));
    }

    return 0;
}
