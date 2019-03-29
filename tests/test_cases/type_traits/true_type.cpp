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
#include <bml/type_traits/true_type.hpp>
#include <bml/type_traits/bool_constant.hpp>

auto test_main() noexcept -> int
{
    // Check that true_type is an alias for bool_constant<true>.
    {
        static_assert(bmltb::is_same<bml::true_type, bml::bool_constant<true>>::value);
    }

    // Check that truth is preserved after assignment.
    {
        bml::true_type t1;
        bml::true_type t2 = t1;

        bmltb_assert(t2);
    }

    return 0;
}
