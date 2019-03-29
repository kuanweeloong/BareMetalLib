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
#include <bml/type_traits/is_referenceable.hpp>

template <typename T>
auto check_referenceable() noexcept -> void
{
    static_assert(bml::is_referenceable<T>::value);
    static_assert(bml::is_referenceable_v<T>);
}

template <typename T>
auto check_not_referenceable() noexcept -> void
{
    static_assert(!bml::is_referenceable<T>::value);
    static_assert(!bml::is_referenceable_v<T>);
}

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type is referenceable.
    {
        check_referenceable<int>();
        check_referenceable<int const>();
        check_referenceable<int[3]>();
        check_referenceable<int volatile[3]>();
        check_referenceable<int*>();
        check_referenceable<int const volatile*>();
        
        check_referenceable<int&>();
        check_referenceable<int const volatile&>();
        check_referenceable<int&&>();
        check_referenceable<int const volatile&&>();
        
        check_referenceable<bmltb::class_type>();
        check_referenceable<bmltb::enum_class>();
        check_referenceable<bmltb::union_type>();
        check_referenceable<bmltb::incomplete_class>();
        check_referenceable<int bmltb::class_type::*>();
        
        check_referenceable<auto () -> void>();
        check_referenceable<auto (int) noexcept -> void>();
        
        check_referenceable<auto (bmltb::class_type::*)() -> void>();
        check_referenceable<auto (bmltb::class_type::*)() & -> void>();
        check_referenceable<auto (bmltb::class_type::*)() && noexcept -> void>();
        check_referenceable<auto (bmltb::class_type::*)() const & -> void>();
        check_referenceable<auto (bmltb::class_type::*)() volatile && noexcept -> void>();
    }
    
    // Check that the result is false when the input type is not referenceable.
    {
        check_not_referenceable<void>();
        
        check_not_referenceable<auto () & -> void>();
        check_not_referenceable<auto () & noexcept -> void>();
        check_not_referenceable<auto () const & -> void>();
        check_not_referenceable<auto () && -> void>();
        check_not_referenceable<auto () const && noexcept -> void>();
    }
    
    return 0;
}
