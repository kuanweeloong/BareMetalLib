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
#include <bml/type_traits/has_unique_object_representations.hpp>

template <typename T>
auto check_has_unique_representation() noexcept -> void
{
    static_assert(bml::has_unique_object_representations<T>::value);
    static_assert(bml::has_unique_object_representations_v<T>);
    
    static_assert(bml::has_unique_object_representations<T const>::value);
    static_assert(bml::has_unique_object_representations_v<T const>);
    
    static_assert(bml::has_unique_object_representations<T volatile>::value);
    static_assert(bml::has_unique_object_representations_v<T volatile>);
    
    static_assert(bml::has_unique_object_representations<T const volatile>::value);
    static_assert(bml::has_unique_object_representations_v<T const volatile>);
}

template <typename T>
auto check_no_unique_representation() noexcept -> void
{
    static_assert(!bml::has_unique_object_representations<T>::value);
    static_assert(!bml::has_unique_object_representations_v<T>);
    
    static_assert(!bml::has_unique_object_representations<T const>::value);
    static_assert(!bml::has_unique_object_representations_v<T const>);
    
    static_assert(!bml::has_unique_object_representations<T volatile>::value);
    static_assert(!bml::has_unique_object_representations_v<T volatile>);
    
    static_assert(!bml::has_unique_object_representations<T const volatile>::value);
    static_assert(!bml::has_unique_object_representations_v<T const volatile>);
}

struct empty {};

struct unique_struct
{
    char a;
    char b;
};

struct non_unique_struct
{
    // Non-unique due to padding.
    char c;
    int i;
};

struct bit_zero
{
    int : 0;
};

union empty_union {};

union unique_union
{
    int a;
    unsigned int b;
};

struct not_trivially_copyable
{
    not_trivially_copyable(not_trivially_copyable const&);
    
    int i;
};

auto test_main() noexcept -> int
{
    // Check that the result is true when the input type has unique object representations. Note
    // that types whose uniqueness is implementation-defined are deliberately left out.
    //
    // TODO: C++20 makes signed integral types (with no padding bits) also have unique
    // representations. Test this when C++20 hits.
    {
        check_has_unique_representation<unsigned int>();
        check_has_unique_representation<unsigned long long>();
        
        check_has_unique_representation<unsigned int[]>();
        check_has_unique_representation<unsigned int[3]>();
        
        check_has_unique_representation<unique_struct>();
        check_has_unique_representation<unique_union>();
    }
    
    // Check that the result is false when the input type does not have unique object
    // representations. Note that types whose uniqueness is implementation-defined are deliberately
    // left out.
    {
        check_no_unique_representation<void>();
        
        check_no_unique_representation<non_unique_struct>();
        check_no_unique_representation<non_unique_struct[]>();
        check_no_unique_representation<non_unique_struct[3]>();
        
        check_no_unique_representation<empty>();
        check_no_unique_representation<empty_union>();
        check_no_unique_representation<bit_zero>();
    }
    
    // Check that the result is false when the input type is not trivially copyable.
    {
        check_no_unique_representation<not_trivially_copyable>();
        
        check_no_unique_representation<int&>();
        check_no_unique_representation<int const&>();
        check_no_unique_representation<int&&>();
        check_no_unique_representation<int(&)[2]>();
        
        check_no_unique_representation<auto (int) -> void>();
        check_no_unique_representation<auto (int) const && noexcept -> void>();
        check_no_unique_representation<auto (&)(int) -> void>();
        check_no_unique_representation<auto (*&&)(int) noexcept -> void>();
    }

    return 0;
}
