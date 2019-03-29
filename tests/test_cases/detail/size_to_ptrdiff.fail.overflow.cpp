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
