//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#include <bml_testbench.hpp>
#include <bml/type_traits/is_destructible.hpp>

template <typename T>
auto check_destructible() noexcept -> void
{
    static_assert(bml::is_destructible<T>::value);
    static_assert(bml::is_destructible_v<T>);
    
    static_assert(bml::is_destructible<T const>::value);
    static_assert(bml::is_destructible_v<T const>);
    
    static_assert(bml::is_destructible<T volatile>::value);
    static_assert(bml::is_destructible_v<T volatile>);
    
    static_assert(bml::is_destructible<T const volatile>::value);
    static_assert(bml::is_destructible_v<T const volatile>);
}

template <typename T>
auto check_not_destructible() noexcept -> void
{
    static_assert(!bml::is_destructible<T>::value);
    static_assert(!bml::is_destructible_v<T>);
    
    static_assert(!bml::is_destructible<T const>::value);
    static_assert(!bml::is_destructible_v<T const>);
    
    static_assert(!bml::is_destructible<T volatile>::value);
    static_assert(!bml::is_destructible_v<T volatile>);
    
    static_assert(!bml::is_destructible<T const volatile>::value);
    static_assert(!bml::is_destructible_v<T const volatile>);
}

struct empty {};

struct bit_zero
{
    int : 0;
};

struct public_abstract    { public:    virtual void foo() = 0; };
struct protected_abstract { protected: virtual void foo() = 0; };
struct private_abstract   { private:   virtual void foo() = 0; };

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
    // Check that the result is true when the input is destructible.
    {
        check_destructible<int>();
        check_destructible<int&>();
        check_destructible<int&&>();
        check_destructible<int*>();
        check_destructible<int const*>();
        check_destructible<int[3]>();
        check_destructible<int[3][2]>();
        check_destructible<int(*)[]>();
        check_destructible<int(&)[]>();
        check_destructible<int(&&)[]>();
        check_destructible<int(*)[][3]>();
        check_destructible<int(&)[][3]>();
        check_destructible<int(&&)[][3]>();
        check_destructible<double>();
        check_destructible<char>();
        
        check_destructible<empty>();
        check_destructible<bit_zero>();
        check_destructible<bmltb::class_type>();
        check_destructible<bmltb::class_type*>();
        check_destructible<bmltb::enum_class>();
        check_destructible<bmltb::union_type>();
        check_destructible<bmltb::union_type&>();
        check_destructible<bmltb::incomplete_class*>();
        
        check_destructible<auto (*)(int) noexcept -> void>();
        check_destructible<auto (&)(int) noexcept -> void>();
        check_destructible<auto (&&)(int) noexcept -> void>();
        
        check_destructible<int bmltb::class_type::*>();
        check_destructible<auto (bmltb::class_type::*)() -> void>();
        check_destructible<auto (bmltb::class_type::*)() const volatile && noexcept -> void>();
        
        check_destructible<public_abstract>();
        check_destructible<protected_abstract>();
        check_destructible<private_abstract>();
        
        check_destructible<public_dtor>();
        check_destructible<virt_public_dtor>();
        check_destructible<pure_public_dtor>();
    }
    
    // Check that the result is false when the input is not destructible.
    {
        check_not_destructible<void>();
        check_not_destructible<int[]>();
        check_not_destructible<int[][3]>();
        
        check_not_destructible<auto (int) -> void>();
        check_not_destructible<auto (int, ...) -> void>();
        check_not_destructible<auto (char) const volatile & noexcept -> void>();
        check_not_destructible<auto (...) const && noexcept -> void>();
        
        check_not_destructible<bmltb::union_type[]>();
        check_not_destructible<bmltb::incomplete_class*[][2]>();
        
        check_not_destructible<protected_dtor>();
        check_not_destructible<private_dtor>();
        
        check_not_destructible<virt_protected_dtor>();
        check_not_destructible<virt_private_dtor>();
        
        check_not_destructible<pure_protected_dtor>();
        check_not_destructible<pure_private_dtor>();
        
        check_not_destructible<del_public_dtor>();
        check_not_destructible<del_protected_dtor>();
        check_not_destructible<del_private_dtor>();
        
        check_not_destructible<del_virt_public_dtor>();
        check_not_destructible<del_virt_protected_dtor>();
        check_not_destructible<del_virt_private_dtor>();
    }

    return 0;
}
