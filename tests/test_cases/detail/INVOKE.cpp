//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/detail/INVOKE.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/utilities/move.hpp>
#include <bml/utilities/reference_wrapper.hpp>

struct no_copy
{
    no_copy() noexcept = default;
    no_copy(no_copy const&) = delete;
    auto operator=(no_copy const&) -> no_copy& = delete;
};

struct base
{
    int m_i;
    
    constexpr explicit base(int i) noexcept : m_i(i) {}
    
    auto operator()(no_copy&&) & noexcept -> int& { return m_i; }
    constexpr auto operator()(no_copy&&) const & noexcept -> int const& { return m_i; }
    auto operator()(no_copy&&) volatile & noexcept -> int volatile& { return m_i; }
    auto operator()(no_copy&&) const volatile & noexcept -> int const volatile& { return m_i; }
    
    auto operator()(no_copy&&) && noexcept -> int&& { return bml::move(m_i); }
    constexpr auto operator()(no_copy&&) const && noexcept -> int const&& { return bml::move(m_i); }
    auto operator()(no_copy&&) volatile && noexcept -> int volatile&& { return bml::move(m_i); }
    auto operator()(no_copy&&) const volatile && noexcept -> int const volatile&&
    {
        return bml::move(m_i);
    }
    
    base(base const&) = delete;
    auto operator=(base const&) -> base& = delete;
};

struct derived : base
{
    constexpr explicit derived(int i) noexcept : base(i) {}
};

auto foo(no_copy&&) noexcept -> int&
{
    static int i = 42;
    return i;
}

constexpr auto constexpr_i = 42;

constexpr auto constexpr_foo(no_copy&&) noexcept -> int const&
{
    return constexpr_i;
}

template <typename Signature, typename ExpectedRet, typename T>
constexpr auto mem_fun_invoked(T&& t) noexcept -> bool
{
    auto ptr = static_cast<Signature base::*>(&base::operator());
    auto arg = no_copy();
    
    // Check return type.
    using Ret = decltype(bml::detail::INVOKE(ptr, bml::forward<T>(t), bml::move(arg)));
    static_assert(bml::is_same_v<Ret, ExpectedRet>);
    
    // Check return value.
    return bml::detail::INVOKE(ptr, bml::forward<T>(t), bml::move(arg)) == 42;
}

template <typename VarType, typename T>
constexpr auto mem_var_invoked(T&& t) noexcept -> bool
{
    auto ptr = &base::m_i;
    
    // Check return type.
    using Ret = decltype(bml::detail::INVOKE(ptr, bml::forward<T>(t)));
    static_assert(bml::is_same_v<Ret, VarType>);
    
    // Check return value.
    return bml::detail::INVOKE(ptr, bml::forward<T>(t)) == 42;
}

template <typename ExpectedRet, typename T>
constexpr auto other_invoked(T&& t) noexcept -> bool
{
    auto arg = no_copy();
    
    // Check return type.
    using Ret = decltype(bml::detail::INVOKE(bml::forward<T>(t), bml::move(arg)));
    static_assert(bml::is_same_v<Ret, ExpectedRet>);
    
    // Check return value.
    return bml::detail::INVOKE(bml::forward<T>(t), bml::move(arg)) == 42;
}

template <typename... Ts>
constexpr auto check_invoke_failed(Ts&&... args) noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::detail::INVOKE(bml::forward<Ts>(args)...)),
        bml::detail::INVOKE_failure>);
}

constexpr auto global_base = base(42);
constexpr auto global_derived = derived(42);

auto test_main() noexcept -> int
{
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to (t1.*f)(t2, ..., tN) when f is a
    // pointer to a member function of a class T and is_base_of_v<T, decay_ty<decltype(t1)>> is true
    // (i.e. bullet 1.1 of [func.require] in N4659 - the C++17 final working draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        // Via base class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(b));
        
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) && noexcept -> int&&, int&&>(bml::move(b)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const && noexcept -> int const&&,
            int const&&>(bml::move(b)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile && noexcept -> int volatile&&,
            int volatile&&>(bml::move(b)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile && noexcept -> int const volatile&&,
            int const volatile&&>(bml::move(b)));
        
        // Via derived class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(d));
        
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) && noexcept -> int&&,
            int&&>(bml::move(d)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const && noexcept -> int const&&,
            int const&&>(bml::move(d)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile && noexcept -> int volatile&&,
            int volatile&&>(bml::move(d)));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile && noexcept -> int const volatile&&,
            int const volatile&&>(bml::move(d)));
        
        // Constexpr context.
        constexpr auto cb = base(42);
        constexpr auto cd = derived(42);
        
        // Via base class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(cb));
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const && noexcept -> int const&&,
            int const&&>(bml::move(cb)));
        
        // Via derived class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(cd));
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const && noexcept -> int const&&,
            int const&&>(bml::move(cd)));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to (t1.get().*f)(t2, ..., tN) when f is a
    // pointer to a member function of a class T and decay_ty<decltype(t1)> is a specialization of
    // reference_wrapper (i.e. bullet 1.2 of [func.require] in N4659 - the C++17 final working
    // draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        auto b_ref = bml::reference_wrapper(b);
        auto d_ref = bml::reference_wrapper(d);
        
        // Via reference_wrapper to base class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(b_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(b_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(b_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(b_ref));
        
        // Via reference_wrapper to derived class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(d_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(d_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(d_ref));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(d_ref));
        
        // Constexpr context.
        constexpr auto cb_ref = bml::reference_wrapper(global_base);
        constexpr auto cd_ref = bml::reference_wrapper(global_derived);
        
        // Via reference_wrapper to base class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(cb_ref));
        
        // Via reference_wrapper to derived class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(cd_ref));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to ((*t1).*f)(t2, ..., tN) when f is a
    // pointer to a member function of a class T and t1 does not satisfy the previous two items
    // (i.e. bullet 1.3 of [func.require] in N4659 - the C++17 final working draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        // Via pointer to base class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(&b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(&b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(&b));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(&b));
        
        // Via pointer to derived class.
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) & noexcept -> int&,
            int&>(&d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(&d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) volatile & noexcept -> int volatile&,
            int volatile&>(&d));
        bmltb_assert(mem_fun_invoked<
            auto (no_copy&&) const volatile & noexcept -> int const volatile&,
            int const volatile&>(&d));
        
        // Constexpr context.
        constexpr auto cb = base(42);
        constexpr auto cd = derived(42);
        
        // Via pointer to base class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(&cb));
        
        // Via pointer to derived class.
        static_assert(mem_fun_invoked<
            auto (no_copy&&) const & noexcept -> int const&,
            int const&>(&cd));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to t1.*f when N == 1 and f is a pointer
    // to data member of a class T and is_base_of_v<T, decay_ty<decltype(t1)>> is true (i.e. bullet
    // 1.4 of [func.require] in N4659 - the C++17 final working draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        // Via base class.
        bmltb_assert(mem_var_invoked<int&>(b));
        bmltb_assert(mem_var_invoked<int const&>(static_cast<base const&>(b)));
        bmltb_assert(mem_var_invoked<int volatile&>(static_cast<base volatile&>(b)));
        bmltb_assert(mem_var_invoked<int const volatile&>(static_cast<base const volatile&>(b)));
        
        // Via derived class.
        bmltb_assert(mem_var_invoked<int&>(d));
        bmltb_assert(mem_var_invoked<int const&>(static_cast<derived const&>(d)));
        bmltb_assert(mem_var_invoked<int volatile&>(static_cast<derived volatile&>(d)));
        bmltb_assert(mem_var_invoked<int const volatile&>(static_cast<derived const volatile&>(d)));
        
        // Constexpr context.
        constexpr auto cb = base(42);
        constexpr auto cd = derived(42);
        
        // Via base class.
        static_assert(mem_var_invoked<int const&>(cb));
        
        // Via derived class.
        static_assert(mem_var_invoked<int const&>(cd));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to t1.get().*f when N == 1 and f is a
    // pointer to data member of a class T and decay_ty<decltype(t1)> is a specialization of
    // reference_wrapper (i.e. bullet 1.5 of [func.require] in N4659 - the C++17 final working
    // draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        auto b_ref    = bml::reference_wrapper(b);
        auto b_ref_c  = bml::reference_wrapper<base const>(b);
        auto b_ref_v  = bml::reference_wrapper<base volatile>(b);
        auto b_ref_cv = bml::reference_wrapper<base const volatile>(b);
        
        auto d_ref    = bml::reference_wrapper(d);
        auto d_ref_c  = bml::reference_wrapper<derived const>(d);
        auto d_ref_v  = bml::reference_wrapper<derived volatile>(d);
        auto d_ref_cv = bml::reference_wrapper<derived const volatile>(d);
        
        // Via reference_wrapper to base class.
        bmltb_assert(mem_var_invoked<int&>(b_ref));
        bmltb_assert(mem_var_invoked<int const&>(b_ref_c));
        bmltb_assert(mem_var_invoked<int volatile&>(b_ref_v));
        bmltb_assert(mem_var_invoked<int const volatile&>(b_ref_cv));
        
        // Via reference_wrapper to derived class.
        bmltb_assert(mem_var_invoked<int&>(d_ref));
        bmltb_assert(mem_var_invoked<int const&>(d_ref_c));
        bmltb_assert(mem_var_invoked<int volatile&>(d_ref_v));
        bmltb_assert(mem_var_invoked<int const volatile&>(d_ref_cv));
        
        // Constexpr context.
        constexpr auto cb_ref = bml::reference_wrapper(global_base);
        constexpr auto cd_ref = bml::reference_wrapper(global_derived);
        
        // Via reference_wrapper to base class.
        static_assert(mem_var_invoked<int const&>(cb_ref));
        
        // Via reference_wrapper to derived class.
        static_assert(mem_var_invoked<int const&>(cd_ref));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to (*t1).*f when N == 1 and f is a
    // pointer to data member of a class T and t1 does not satisfy the previous two items (i.e.
    // bullet 1.6 of [func.require] in N4659 - the C++17 final working draft).
    {
        // Non-constexpr context.
        auto b = base(42);
        auto d = derived(42);
        
        // Via pointer to base class.
        bmltb_assert(mem_var_invoked<int&>(&b));
        bmltb_assert(mem_var_invoked<int const&>(static_cast<base const*>(&b)));
        bmltb_assert(mem_var_invoked<int volatile&>(static_cast<base volatile*>(&b)));
        bmltb_assert(mem_var_invoked<int const volatile&>(static_cast<base const volatile*>(&b)));
        
        // Via pointer to derived class.
        bmltb_assert(mem_var_invoked<int&>(&d));
        bmltb_assert(mem_var_invoked<int const&>(static_cast<derived const*>(&d)));
        bmltb_assert(mem_var_invoked<int volatile&>(static_cast<derived volatile*>(&d)));
        bmltb_assert(mem_var_invoked<int const volatile&>(
            static_cast<derived const volatile*>(&d)));
        
        // Constexpr context.
        constexpr auto cb = base(42);
        constexpr auto cd = derived(42);
        
        // Via pointer to base class.
        static_assert(mem_var_invoked<int const&>(static_cast<base const*>(&cb)));
        
        // Via pointer to derived class.
        static_assert(mem_var_invoked<int const&>(static_cast<derived const*>(&cd)));
    }
    
    // Check that INVOKE(f, t1, t2, ..., tN) is equivalent to f(t1, t2, ..., tN) in all other cases
    // (i.e. bullet 1.7 of [func.require] in N4659 - the C++17 final working draft).
    {
        // Invoke reference to free function.
        auto& ref = foo;
        constexpr auto& cref = constexpr_foo;
        
        bmltb_assert(other_invoked<int&>(ref));
        static_assert(other_invoked<int const&>(cref));
        
        // Invoke pointer to free function.
        auto ptr = foo;
        constexpr auto cptr = constexpr_foo;
        
        bmltb_assert(other_invoked<int&>(ptr));
        static_assert(other_invoked<int const&>(cptr));
        
        // Invoke function object.
        auto b = base(42);
        constexpr auto cb = base(42);
        
        bmltb_assert(other_invoked<int&>(b));
        bmltb_assert(other_invoked<int const&>(static_cast<base const&>(b)));
        bmltb_assert(other_invoked<int volatile&>(static_cast<base volatile&>(b)));
        bmltb_assert(other_invoked<int const volatile&>(static_cast<base const volatile&>(b)));
        
        bmltb_assert(other_invoked<int&&>(static_cast<base&&>(b)));
        bmltb_assert(other_invoked<int const&&>(static_cast<base const&&>(b)));
        bmltb_assert(other_invoked<int volatile&&>(static_cast<base volatile&&>(b)));
        bmltb_assert(other_invoked<int const volatile&&>(static_cast<base const volatile&&>(b)));
        
        static_assert(other_invoked<int const&>(cb));
        static_assert(other_invoked<int const&&>(bml::move(cb)));
    }
    
    // Check that INVOKE yields the invoke_failed tag type when its arguments do not form an
    // invocable expression.
    {
        auto b = base(42);
        auto b_ref = bml::reference_wrapper(b);
        auto b_fn = static_cast<auto (base::*)(no_copy&&) & noexcept -> int&>(&base::operator());
        
        auto& f_ref = foo;
        auto f_ptr = foo;
        
        auto not_func_obj = bmltb::class_type();
        
        check_invoke_failed(b_fn);
        check_invoke_failed(b_fn, b);
        check_invoke_failed(b_fn, b_ref);
        check_invoke_failed(b_fn, b, no_copy(), 2);
        check_invoke_failed(b_fn, b, 1, 2, 3.0);
        
        check_invoke_failed(b);
        check_invoke_failed(b, b_fn);
        check_invoke_failed(b, b_fn, 5, 4, b);
        check_invoke_failed(b, b);
        check_invoke_failed(b, b_ref);
        
        check_invoke_failed(b_ref);
        check_invoke_failed(b_ref, b_fn);
        check_invoke_failed(b_ref, b_fn, 5, 4, b);
        check_invoke_failed(b_ref, b);
        
        check_invoke_failed(f_ref);
        check_invoke_failed(f_ref, f_ref);
        check_invoke_failed(f_ref, no_copy(), 2);
        check_invoke_failed(f_ref, 1.3f, 2, 3);
        
        check_invoke_failed(f_ptr);
        check_invoke_failed(f_ptr, no_copy(), no_copy());
        check_invoke_failed(f_ptr, 1.3f, 2, 3);
        
        check_invoke_failed(not_func_obj);
    }
    
    return 0;
}
