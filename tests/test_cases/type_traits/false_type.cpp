//
// Copyright (c) 2018 Wee Loong Kuan
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
#include <bml/type_traits/false_type.hpp>
#include <bml/type_traits/bool_constant.hpp>

auto test_main() noexcept -> int
{
    // Check that false_type is an alias for bool_constant<false>.
    {
        static_assert(bmltb::is_same<bml::false_type, bml::bool_constant<false>>::value);
    }

    // Check that non-truth is preserved after assignment.
    {
        bml::false_type f1;
        bml::false_type f2 = f1;

        bmltb_assert(!f2);
    }

    return 0;
}
