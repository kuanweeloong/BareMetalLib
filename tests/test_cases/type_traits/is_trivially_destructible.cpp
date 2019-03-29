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
#include <bml/type_traits/is_trivially_destructible.hpp>

template <typename T>
auto check_trivially_destructible() noexcept -> void
{
    static_assert(bml::is_trivially_destructible<T>::value);
    static_assert(bml::is_trivially_destructible_v<T>);
    
    static_assert(bml::is_trivially_destructible<T const>::value);
    static_assert(bml::is_trivially_destructible_v<T const>);
    
    static_assert(bml::is_trivially_destructible<T volatile>::value);
    static_assert(bml::is_trivially_destructible_v<T volatile>);
    
    static_assert(bml::is_trivially_destructible<T const volatile>::value);
    static_assert(bml::is_trivially_destructible_v<T const volatile>);
}

template <typename T>
auto check_not_trivially_destructible() noexcept -> void
{
    static_assert(!bml::is_trivially_destructible<T>::value);
    static_assert(!bml::is_trivially_destructible_v<T>);
    
    static_assert(!bml::is_trivially_destructible<T const>::value);
    static_assert(!bml::is_trivially_destructible_v<T const>);
    
    static_assert(!bml::is_trivially_destructible<T volatile>::value);
    static_assert(!bml::is_trivially_destructible_v<T volatile>);
    
    static_assert(!bml::is_trivially_destructible<T const volatile>::value);
    static_assert(!bml::is_trivially_destructible_v<T const volatile>);
}

struct empty {};

union empty_union {};

struct bit_zero
{
    int : 0;
};

struct public_abstract    { public:    virtual auto foo() -> void = 0; };
struct protected_abstract { protected: virtual auto foo() -> void = 0; };
struct private_abstract   { private:   virtual auto foo() -> void = 0; };

struct public_dtor    { public:    ~public_dtor()    {} };
struct protected_dtor { protected: ~protected_dtor() {} };
struct private_dtor   { private:   ~private_dtor()   {} };

struct virt_public_dtor    { public:    virtual ~virt_public_dtor()    {} };
struct virt_protected_dtor { protected: virtual ~virt_protected_dtor() {} };
struct virt_private_dtor   { private:   virtual ~virt_private_dtor()   {} };

struct pure_public_dtor    { public:    virtual ~pure_public_dtor()    = 0; };
struct pure_protected_dtor { protected: virtual ~pure_protected_dtor() = 0; };
struct pure_private_dtor   { private:   virtual ~pure_private_dtor()   = 0; };

struct del_public_dtor    { public:    ~del_public_dtor()    = delete; };
struct del_protected_dtor { protected: ~del_protected_dtor() = delete; };
struct del_private_dtor   { private:   ~del_private_dtor()   = delete; };

struct del_virt_public_dtor    { public:    virtual ~del_virt_public_dtor()    = delete; };
struct del_virt_protected_dtor { protected: virtual ~del_virt_protected_dtor() = delete; };
struct del_virt_private_dtor   { private:   virtual ~del_virt_private_dtor()   = delete; };

auto test_main() noexcept -> int
{
    // Check that the result is true when the input is trivially destructible.
    {
        check_trivially_destructible<int>();
        check_trivially_destructible<int&>();
        check_trivially_destructible<int&&>();
        check_trivially_destructible<int*>();
        check_trivially_destructible<int const*>();
        check_trivially_destructible<int[3]>();
        check_trivially_destructible<int[3][2]>();
        check_trivially_destructible<int(*)[]>();
        check_trivially_destructible<int(&)[]>();
        check_trivially_destructible<int(&&)[]>();
        check_trivially_destructible<int(*)[][3]>();
        check_trivially_destructible<int(&)[][3]>();
        check_trivially_destructible<int(&&)[][3]>();
        check_trivially_destructible<double>();
        check_trivially_destructible<char>();
        
        check_trivially_destructible<empty>();
        check_trivially_destructible<empty_union>();
        check_trivially_destructible<bit_zero>();
        check_trivially_destructible<bmltb::class_type*>();
        check_trivially_destructible<bmltb::enum_class>();
        check_trivially_destructible<bmltb::union_type&>();
        check_trivially_destructible<bmltb::incomplete_class*>();
        
        check_trivially_destructible<auto (*)(int) noexcept -> void>();
        check_trivially_destructible<auto (&)(int) noexcept -> void>();
        check_trivially_destructible<auto (&&)(int) noexcept -> void>();
        
        check_trivially_destructible<int bmltb::class_type::*>();
        check_trivially_destructible<auto (bmltb::class_type::*)() -> void>();
        check_trivially_destructible<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_trivially_destructible<public_abstract>();
        check_trivially_destructible<protected_abstract>();
        check_trivially_destructible<private_abstract>();
    }
    
    // Check that the result is false when the input is not trivially destructible.
    {
        check_not_trivially_destructible<public_dtor>();
        check_not_trivially_destructible<virt_public_dtor>();
        check_not_trivially_destructible<pure_public_dtor>();
    }
    
    // Check that the result is false when the input is not destructible.
    {
        check_not_trivially_destructible<void>();
        check_not_trivially_destructible<int[]>();
        check_not_trivially_destructible<int[][3]>();
        
        check_not_trivially_destructible<auto (int) -> void>();
        check_not_trivially_destructible<auto (int, ...) -> void>();
        check_not_trivially_destructible<auto (char) const volatile & noexcept -> void>();
        check_not_trivially_destructible<auto (...) const && noexcept -> void>();
        
        check_not_trivially_destructible<bmltb::union_type[]>();
        check_not_trivially_destructible<bmltb::incomplete_class*[][2]>();
        
        check_not_trivially_destructible<protected_dtor>();
        check_not_trivially_destructible<private_dtor>();
        
        check_not_trivially_destructible<virt_protected_dtor>();
        check_not_trivially_destructible<virt_private_dtor>();
        
        check_not_trivially_destructible<pure_protected_dtor>();
        check_not_trivially_destructible<pure_private_dtor>();
        
        check_not_trivially_destructible<del_public_dtor>();
        check_not_trivially_destructible<del_protected_dtor>();
        check_not_trivially_destructible<del_private_dtor>();
        
        check_not_trivially_destructible<del_virt_public_dtor>();
        check_not_trivially_destructible<del_virt_protected_dtor>();
        check_not_trivially_destructible<del_virt_private_dtor>();
    }

    return 0;
}
