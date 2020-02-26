//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/utilities/reference_wrapper.hpp>
#include <bml/utilities/addressof.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_constructible.hpp>
#include <bml/type_traits/is_trivially_copyable.hpp>

constexpr auto global_cint = 3;

struct overloaded_addr
{
    auto operator&() -> overloaded_addr* { return nullptr; }
};

constexpr auto foo() -> int { return 42; }

struct no_copy
{
    no_copy(no_copy const&) = delete;
    auto operator=(no_copy const&) = delete;
};

struct dest {};
dest gloabl_dest;

struct convertible_to_dest_ref
{
    operator dest&() { return gloabl_dest; }
};
struct convertible_to_dest_temp
{
    operator dest() { return dest(); }
};
struct not_convertible_to_dest {};

auto convertible_int_ref(int&) -> bool { return true; }
constexpr auto convertible_cint_ref(int const&) -> bool { return true; }

struct base
{
    int m_i;
    
    constexpr base() : m_i(42) {}
    
    constexpr auto operator()(int i) const noexcept -> int { return i; }
    constexpr auto operator()(double d) const noexcept -> double { return d; }
};

struct derived : base {};

constexpr auto global_derived = derived();
constexpr auto base_int_op = static_cast<auto (base::*)(int) const noexcept -> int>(
    &base::operator());
constexpr auto base_double_op = static_cast<auto (base::*)(double) const noexcept -> double>(
    &base::operator());
constexpr auto base_int_mem = &base::m_i;

constexpr auto bar(int i) noexcept -> int
{
    return i;
}

auto void_fun_count = 0;

auto void_fun() noexcept -> void
{
    ++void_fun_count;
}

auto test_main() noexcept -> int
{
    // Check that the member type alias "type" names the type being referenced.
    {
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int>::type, int>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int const>::type, int const>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int volatile>::type,
            int volatile>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int const volatile>::type,
            int const volatile>);
        
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int[3]>::type, int[3]>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int const[]>::type,
            int const[]>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<int* const>::type,
            int* const>);
        
        static_assert(bml::is_same_v<typename bml::reference_wrapper<bmltb::class_type>::type,
            bmltb::class_type>);
        static_assert(bml::is_same_v<typename bml::reference_wrapper<bmltb::union_type>::type,
            bmltb::union_type>);
        
        static_assert(bml::is_same_v<typename bml::reference_wrapper<auto () -> int>::type,
            auto () -> int>);
        static_assert(bml::is_same_v<
            typename bml::reference_wrapper<auto (bmltb::class_type::*)(int) -> void>::type,
            auto (bmltb::class_type::*)(int) -> void>);
    }
    
    // Check that the stored reference refers to the same object referred to by the reference passed
    // in during construction.
    {
        // Non-constexpr context.
        auto obj = bmltb::class_type();
        auto wrapper = bml::reference_wrapper<bmltb::class_type>(obj);
        bmltb_assert(&wrapper.get() == &obj);
        
        // Constexpr context.
        constexpr auto cint_wrapper = bml::reference_wrapper<int const>(global_cint);
        static_assert(&cint_wrapper.get() == &global_cint);
        
        constexpr auto cfun_wrapper = bml::reference_wrapper<auto () -> int>(foo);
        static_assert(&cfun_wrapper.get() == &foo);
        
        // Overloaded addressof.
        auto addr_obj = overloaded_addr();
        auto addr_wrapper = bml::reference_wrapper<overloaded_addr>(addr_obj);
        bmltb_assert(bml::addressof(addr_wrapper.get()) == bml::addressof(addr_obj));
    }
    
    // Check that reference_wrapper is constructible from objects implicitly convertible to T&,
    // where T is the type being wrapped.
    {
        static_assert(bml::is_constructible_v<bml::reference_wrapper<dest>,
            convertible_to_dest_ref>);
    }
    
    // Check that reference_wrapper is not constructible from:
    //   1. Other reference_wrappers which also wrap T, unless the reference_wrapper is being
    //      copied.
    //   2. Objects not implicitly convertible to T&.
    //   3. Temporaries.
    {
        // Other reference_wrappers also wrapping T, except for copying case.
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<int>,
            bml::reference_wrapper<int> volatile>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<int>,
            bml::reference_wrapper<int> volatile&>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<int>,
            bml::reference_wrapper<int> const volatile>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<int>,
            bml::reference_wrapper<int> const volatile&>);
        
        // Objects not implicitly convertible to T&.
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            not_convertible_to_dest>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            not_convertible_to_dest&>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            not_convertible_to_dest&&>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            convertible_to_dest_temp>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            convertible_to_dest_temp&>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>,
            convertible_to_dest_temp&&>);
        
        // Temporaries
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>, dest>);
        static_assert(!bml::is_constructible_v<bml::reference_wrapper<dest>, dest&&>);
    }
    
    // Check that copied reference_wrappers refer to the same object.
    {
        auto i = 42;
        auto j = 100;
        auto orig = bml::reference_wrapper<int>(i);
        auto copy = bml::reference_wrapper<int>(j);
        copy = orig;
        
        bmltb_assert(&copy.get() == &orig.get());
        
        constexpr auto corig = bml::reference_wrapper<int const>(global_cint);
        constexpr auto ccopy = corig;
        
        static_assert(&corig.get() == &ccopy.get());
    }
    
    // Check that reference_wrapper is trivially copyable.
    {
        static_assert(bml::is_trivially_copyable_v<bml::reference_wrapper<int>>);
        static_assert(bml::is_trivially_copyable_v<bml::reference_wrapper<int[3]>>);
        static_assert(bml::is_trivially_copyable_v<bml::reference_wrapper<int[]>>);
        static_assert(bml::is_trivially_copyable_v<bml::reference_wrapper<auto () -> void>>);
        
        static_assert(bml::is_trivially_copyable_v<bml::reference_wrapper<no_copy>>);
    }
    
    // Check that reference_wrapper is implicitly convertible to the underlying reference.
    {
        // Non-constexpr context.
        auto i = 42;
        auto r = bml::reference_wrapper<int>(i);
        bmltb_assert(convertible_int_ref(r));
        
        // Constexpr context.
        constexpr auto cr = bml::reference_wrapper<int const>(global_cint);
        static_assert(convertible_cint_ref(cr));
    }
    
    // Check that reference_wrappers can be invoked.
    {
        // Pointer to member functions.
        constexpr auto d = derived();
        
        constexpr auto int_op =
            bml::reference_wrapper<auto (base::* const)(int) const noexcept -> int>(base_int_op);
        constexpr auto double_op =
            bml::reference_wrapper<auto (base::* const)(double) const noexcept -> double>(
                base_double_op);
        
        static_assert(bml::is_same_v<decltype(int_op(d, 100)), int>);
        static_assert(int_op(d, 100) == 100);
        
        static_assert(bml::is_same_v<decltype(double_op(d, 100)), double>);
        static_assert(double_op(d, 100.0) == 100.0);
        
        // Pointer to data member.
        constexpr auto int_mem = bml::reference_wrapper<int base::* const>(base_int_mem);
        
        static_assert(bml::is_same_v<decltype(int_mem(d)), int const&>);
        static_assert(int_mem(d) == 42);
        
        // Free function.
        constexpr auto bar_ref = bml::reference_wrapper<auto (int) noexcept -> int>(bar);
        
        static_assert(bml::is_same_v<decltype(bar_ref(123)), int>);
        static_assert(bar_ref(123) == 123);
        
        auto void_fun_ref = bml::reference_wrapper<auto () noexcept -> void>(void_fun);
        
        static_assert(bml::is_same_v<decltype(void_fun_ref()), void>);
        auto void_fun_count_before = void_fun_count;
        void_fun_ref();
        bmltb_assert(void_fun_count == void_fun_count_before + 1);
        
        // Function object.
        constexpr auto d_ref = bml::reference_wrapper<derived const>(global_derived);
        
        static_assert(bml::is_same_v<decltype(d_ref(999)), int>);
        static_assert(d_ref(999) == 999);
        
        static_assert(bml::is_same_v<decltype(d_ref(999.9)), double>);
        static_assert(d_ref(999.9) == 999.9);
    }
    
    // Check that reference_wrapper's class template deduces a reference to the input argument's
    // type.
    {
        // Non-constexpr context.
        auto i = 42;
        auto r = bml::reference_wrapper(i);
        
        static_assert(bml::is_same_v<decltype(r), bml::reference_wrapper<int>>);
        
        // Constexpr context.
        constexpr auto cr = bml::reference_wrapper(global_cint);
        
        static_assert(bml::is_same_v<decltype(cr), bml::reference_wrapper<int const> const>);
    }
    
    return 0;
}
