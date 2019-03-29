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

#include <bml_testbench.hpp>
#include <bml/utilities/launder.hpp>
#include <bml/utilities/new.hpp>
#include <bml/type_traits/aligned_storage.hpp>

struct x
{
    int const n;
};

auto test_main() noexcept -> int
{
    // Check that launder's result does not point to a different address than its argument.
    {
        constexpr auto i = 1;
        auto const* pi = &i;
        
        static_assert(bml::launder(&i) == &i);
        bmltb_assert(bml::launder(pi) == pi);
        
        constexpr auto f = 2.f;
        auto const* pf = &f;
        
        static_assert(bml::launder(&f) == &f);
        bmltb_assert(bml::launder(pf) == pf);
    }
    
    // Check that launder returns a pointer to the new object when given a pointer to the object's
    // backing storage.
    {
        auto storage = bml::aligned_storage_ty<sizeof(int), alignof(int)>();
        
        static_cast<void>(::new (&storage) int(10));
        bmltb_assert(*bml::launder(reinterpret_cast<int*>(&storage)) == 10);
    }
    
    // Check that launder returns a pointer to the new object when an object with const-qualified
    // members has been constructed in the storage location of another object of the same type.
    {
        auto storage = bml::aligned_storage_ty<sizeof(x), alignof(x)>();
        
        auto p = ::new (&storage) x{1};
        bmltb_assert(p->n == 1);
        
        static_cast<void>(::new (&storage) x{2});
        bmltb_assert(bml::launder(p)->n == 2);
    }
    
    return 0;
}
