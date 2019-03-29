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
    // Check that the result is of type ::ptrdiff_t.
    {
        static_assert(bml::is_same_v<
            decltype(bml::detail::size_to_ptrdiff<static_cast<::size_t>(0)>()), ::ptrdiff_t>);
    }
    
    // Check that the result is the same as the input when the input is less than PTRDIFF_MAX.
    {
        static_assert(bml::detail::size_to_ptrdiff<static_cast<::size_t>(0)>() == 0);
        static_assert(bml::detail::size_to_ptrdiff<static_cast<::size_t>(35)>() == 35);
        static_assert(bml::detail::size_to_ptrdiff<static_cast<::size_t>(80)>() == 80);
        static_assert(bml::detail::size_to_ptrdiff<static_cast<::size_t>(PTRDIFF_MAX)>()
            == PTRDIFF_MAX);
    }
    
    return 0;
}
