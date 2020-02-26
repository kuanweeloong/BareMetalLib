//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <stddef.h>
#include <stdint.h>
#include <bml_testbench.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/detail/size_to_ptrdiff.hpp>

auto test_main() noexcept -> int
{
    // Check that a compile error occurs when the input is larger than PTRDIFF_MAX.
    {
        auto i = bml::detail::size_to_ptrdiff<static_cast<::size_t>(PTRDIFF_MAX) + 1>();
    }
    
    return 0;
}
