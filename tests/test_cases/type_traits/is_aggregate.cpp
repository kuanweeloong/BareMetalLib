//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_aggregate.hpp>

template <typename T>
auto check_aggregate() noexcept -> void
{
    static_assert(bml::is_aggregate<T>::value);
    static_assert(bml::is_aggregate_v<T>);
}

template <typename T>
auto check_not_aggregate() noexcept -> void
{
    static_assert(!bml::is_aggregate<T>::value);
    static_assert(!bml::is_aggregate_v<T>);
}

struct aggregate {};
struct has_ctor { has_ctor(int); };
struct prot_mem { protected: int x; };

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is an aggregate.
    {
        check_aggregate<aggregate>();
        check_aggregate<aggregate const>();
        
        check_aggregate<aggregate[]>();
        check_aggregate<aggregate volatile[]>();
        check_aggregate<aggregate const volatile[]>();
        
        check_aggregate<aggregate[10][20]>();
        check_aggregate<aggregate const volatile[10][20]>();
        
        check_aggregate<bmltb::class_type>();
        check_aggregate<bmltb::class_type const volatile>();
        
        check_aggregate<bmltb::union_type>();
        check_aggregate<bmltb::union_type const>();
    }
    
    // Check that the result is false when the input is not an aggregate.
    {
        check_not_aggregate<void>();
        check_not_aggregate<void const>();
        
        check_not_aggregate<void*>();
        check_not_aggregate<void* const>();
        check_not_aggregate<void const*>();
        check_not_aggregate<void const* volatile>();
        
        check_not_aggregate<int>();
        check_not_aggregate<int const&>();
        check_not_aggregate<int const volatile&&>();
        
        check_not_aggregate<auto () noexcept -> void>();
        check_not_aggregate<auto (int) -> void>();
        check_not_aggregate<auto () const & noexcept -> void>();
        
        check_not_aggregate<auto (&)() noexcept -> void>();
        check_not_aggregate<auto (&&)() -> void>();
        
        check_not_aggregate<aggregate*>();
        check_not_aggregate<aggregate volatile* const>();
        
        check_not_aggregate<aggregate&>();
        check_not_aggregate<aggregate const&>();
        check_not_aggregate<aggregate volatile&&>();
        
        check_not_aggregate<int aggregate::*>();
        check_not_aggregate<aggregate aggregate::*>();
        
        check_not_aggregate<auto (aggregate::*)() noexcept -> void>();
        check_not_aggregate<auto (aggregate::*)() && -> void>();
        check_not_aggregate<auto (aggregate::*)() const & noexcept -> void>();
        
        check_not_aggregate<has_ctor>();
        check_not_aggregate<has_ctor const volatile>();
        
        check_not_aggregate<prot_mem>();
        check_not_aggregate<prot_mem const volatile>();
    }

    return 0;
}
