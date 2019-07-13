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
#include <bml/containers/optional.hpp>
#include <bml/type_traits/is_explicitly_constructible.hpp>
#include <bml/type_traits/is_constructible.hpp>
#include <bml/type_traits/is_copy_constructible.hpp>
#include <bml/type_traits/is_trivially_copy_constructible.hpp>
#include <bml/type_traits/is_copy_assignable.hpp>
#include <bml/type_traits/is_trivially_copy_assignable.hpp>
#include <bml/type_traits/is_move_constructible.hpp>
#include <bml/type_traits/is_trivially_move_constructible.hpp>
#include <bml/type_traits/is_move_assignable.hpp>
#include <bml/type_traits/is_trivially_move_assignable.hpp>
#include <bml/type_traits/is_destructible.hpp>
#include <bml/type_traits/is_trivially_destructible.hpp>
#include <bml/type_traits/is_assignable.hpp>
#include <bml/type_traits/is_convertible.hpp>
#include <bml/type_traits/is_swappable.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_aggregate.hpp>
#include <bml/type_traits/is_default_constructible.hpp>
#include <bml/utilities/move.hpp>
#include <bml/utilities/declval.hpp>

struct multiply
{
    int value;
    
    constexpr multiply(int a, int b) : value(a * b) {}
};

struct copy_ctor
{
    int value;
    bool copy_ctor_called;
    
    constexpr copy_ctor(int i) : value(i), copy_ctor_called(false) {}
    constexpr copy_ctor(copy_ctor const& other) : value(other.value), copy_ctor_called(true) {}
    copy_ctor(copy_ctor const volatile& other) : value(other.value), copy_ctor_called(true) {}
    
    auto operator=(copy_ctor const&) -> copy_ctor& = delete;
    copy_ctor(copy_ctor&&) = delete;
    auto operator=(copy_ctor&&) -> copy_ctor& = delete;
};

struct triv_copy_ctor
{
    int value;
    
    constexpr triv_copy_ctor(int i) : value(i) {}
    triv_copy_ctor(triv_copy_ctor const&) = default;
    
    auto operator=(triv_copy_ctor const&) -> triv_copy_ctor& = delete;
    triv_copy_ctor(triv_copy_ctor&&) = delete;
    auto operator=(triv_copy_ctor&&) -> triv_copy_ctor& = delete;
};
static_assert(bml::is_trivially_copy_constructible_v<triv_copy_ctor>);

struct no_copy_ctor
{
    no_copy_ctor(no_copy_ctor const&) = delete;
    
    // Implicit: move constructor not declared.
};
static_assert(!bml::is_move_constructible_v<no_copy_ctor>);

struct implicit_no_copy_ctor
{
    no_copy_ctor m;
};
static_assert(!bml::is_copy_constructible_v<implicit_no_copy_ctor>);
static_assert(!bml::is_move_constructible_v<implicit_no_copy_ctor>);

struct copy_assign
{
    int value;
    bool copy_assign_called;
    
    constexpr copy_assign(int i) : value(i), copy_assign_called(false) {}
    
    // optional needs copy-constructibility for copy-assignment.
    copy_assign(copy_assign const volatile& other)
        : value(other.value), copy_assign_called(false) {}
    
    auto operator=(copy_assign const& other) -> copy_assign&
    {
        value = other.value;
        copy_assign_called = true;
        return *this;
    }
    
    // Returns void instead of volatile reference to stop GCC from emitting warnings about not
    // reading from volatile after assignment.
    auto operator=(copy_assign const volatile& other) volatile -> void
    {
        value = other.value;
        copy_assign_called = true;
    }
    
    copy_assign(copy_assign&&) = delete;
    auto operator=(copy_assign&&) -> copy_assign& = delete;
};

struct triv_copy_assign
{
    int value;
    
    constexpr triv_copy_assign(int i) : value(i) {}
    
    // optional needs copy-constructibility for copy-assignment.
    triv_copy_assign(triv_copy_assign const&) = default;
    
    auto operator=(triv_copy_assign const&) -> triv_copy_assign& = default;
    
    triv_copy_assign(triv_copy_assign&&) = delete;
    auto operator=(triv_copy_assign&&) -> triv_copy_assign& = delete;
};
static_assert(bml::is_trivially_copy_assignable_v<triv_copy_assign>);

struct no_copy_assign
{
    auto operator=(no_copy_assign const&) = delete;
    
    // Implicit: move assignment not declared.
};
static_assert(!bml::is_move_assignable_v<no_copy_assign>);

struct implicit_no_copy_assign
{
    no_copy_assign m;
};
static_assert(!bml::is_copy_assignable_v<implicit_no_copy_assign>);
static_assert(!bml::is_move_assignable_v<implicit_no_copy_assign>);

struct move_ctor
{
    int value;
    bool move_ctor_called;
    
    constexpr move_ctor(int i) : value(i), move_ctor_called(false) {}
    constexpr move_ctor(move_ctor&& other) : value(other.value), move_ctor_called(true) {}
    move_ctor(move_ctor volatile&& other) : value(other.value), move_ctor_called(true) {}
    
    auto operator=(move_ctor&&) -> move_ctor& = delete;
    move_ctor(move_ctor const&) = delete;
    auto operator=(move_ctor const&) -> move_ctor& = delete;
};

struct triv_move_ctor
{
    int value;
    
    constexpr triv_move_ctor(int i) : value(i) {}
    triv_move_ctor(triv_move_ctor&&) = default;
    
    auto operator=(triv_move_ctor&&) -> triv_move_ctor& = delete;
    triv_move_ctor(triv_move_ctor const&) = delete;
    auto operator=(triv_move_ctor const&) -> triv_move_ctor& = delete;
};
static_assert(bml::is_trivially_move_constructible_v<triv_move_ctor>);

struct no_move_ctor
{
    no_move_ctor(no_move_ctor&&) = delete;
    
    // Implicit: copy constructor not declared.
};
static_assert(!bml::is_copy_constructible_v<no_move_ctor>);

struct implicit_no_move_ctor
{
    no_move_ctor m;
};
static_assert(!bml::is_move_constructible_v<implicit_no_move_ctor>);
static_assert(!bml::is_copy_constructible_v<implicit_no_move_ctor>);

struct copy_ctor_no_move_ctor
{
    copy_ctor_no_move_ctor(copy_ctor_no_move_ctor const&) = default;
    copy_ctor_no_move_ctor(copy_ctor_no_move_ctor&&) = delete;
};

struct move_assign
{
    int value;
    bool move_assign_called;
    
    constexpr move_assign(int i) : value(i), move_assign_called(false) {}
    
    // optional needs move-constructibility for move-assignment.
    move_assign(move_assign&& other) : value(other.value), move_assign_called(false) {}
    move_assign(move_assign volatile&& other) : value(other.value), move_assign_called(false) {}
    
    auto operator=(move_assign&& other) -> move_assign&
    {
        value = other.value;
        move_assign_called = true;
        return *this;
    }
    
    // Returns void instead of volatile reference to stop GCC from emitting warnings about not
    // reading from volatile after assignment.
    auto operator=(move_assign volatile&& other) volatile -> void
    {
        value = other.value;
        move_assign_called = true;
    }
    
    move_assign(move_assign const&) = delete;
    auto operator=(move_assign const&) -> move_assign& = delete;
};

struct triv_move_assign
{
    int value;
    
    constexpr triv_move_assign(int i) : value(i) {}
    
    // optional needs move-constructibility for move-assignment.
    triv_move_assign(triv_move_assign&&) = default;
    
    auto operator=(triv_move_assign&&) -> triv_move_assign& = default;
    
    triv_move_assign(triv_move_assign const&) = delete;
    auto operator=(triv_move_assign const&) -> triv_move_assign& = delete;
};
static_assert(bml::is_trivially_move_assignable_v<triv_move_assign>);

struct no_move_assign
{
    auto operator=(no_move_assign&&) = delete;
    
    // Implicit: copy assignment deleted.
};
static_assert(!bml::is_copy_assignable_v<no_move_assign>);

struct implicit_no_move_assign
{
    no_move_assign m;
};
static_assert(!bml::is_move_assignable_v<implicit_no_move_assign>);
static_assert(!bml::is_copy_assignable_v<implicit_no_move_assign>);

struct copyable_no_move_assign
{
    copyable_no_move_assign() = default;
    
    copyable_no_move_assign(copyable_no_move_assign const&) = default;
    auto operator=(copyable_no_move_assign const&) -> copyable_no_move_assign& = default;
    
    auto operator=(copyable_no_move_assign&&) = delete;
};

struct dtor
{
    inline static auto count = 0;
    
    dtor() = default;
    ~dtor() { ++count; }
    
    dtor(dtor const&) = default;
    dtor(dtor&&) = default;
    auto operator=(dtor const&) -> dtor& = default;
    auto operator=(dtor&&) -> dtor& = default;
};

struct triv_dtor
{
    ~triv_dtor() = default;
};
static_assert(bml::is_trivially_destructible_v<triv_dtor>);

struct no_dtor
{
    ~no_dtor() = delete;
};

template <typename O, typename Expected>
constexpr auto check_value_fn_and_indir_op_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::declval<O&>().value()), Expected&>);
    static_assert(bml::is_same_v<decltype(bml::declval<O const&>().value()), Expected const&>);
    
    static_assert(bml::is_same_v<decltype(bml::declval<O>().value()), Expected&&>);
    static_assert(bml::is_same_v<decltype(bml::declval<O const>().value()), Expected const&&>);
    
    static_assert(bml::is_same_v<decltype(*bml::declval<O&>()), Expected&>);
    static_assert(bml::is_same_v<decltype(*bml::declval<O const&>()), Expected const&>);
    
    static_assert(bml::is_same_v<decltype(*bml::declval<O>()), Expected&&>);
    static_assert(bml::is_same_v<decltype(*bml::declval<O const>()), Expected const&&>);
}

template <typename O, typename Expected>
constexpr auto check_mem_of_ptr_op_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::declval<O&>().operator->()), Expected*>);
    static_assert(bml::is_same_v<decltype(bml::declval<O const&>().operator->()), Expected const*>);
}

template <typename O, typename... Args>
constexpr auto can_call_emplace_impl(int) noexcept
    -> decltype(bml::declval<O>().template emplace(bml::declval<Args>()...), true)
{
    return true;
}

template <typename, typename...>
constexpr auto can_call_emplace_impl(...) noexcept -> bool
{
    return false;
}

template <typename O, typename... Args>
constexpr auto can_call_emplace() noexcept -> bool
{
    return can_call_emplace_impl<O, Args...>(0);
}

struct swappee
{
    static inline auto swap_called = false;
    
    int value;
    
    swappee(int i) : value(i) {}
};

auto swap(swappee& lhs, swappee& rhs) noexcept -> void
{
    using bml::swap;
    swap(lhs.value, rhs.value);
    
    swappee::swap_called = true;
}

struct not_swappable {};
auto swap(not_swappable&, not_swappable&) -> void = delete;

template <typename O>
constexpr auto can_call_mem_swap_impl(int) noexcept
    -> decltype(bml::declval<O>().template swap(bml::declval<O&>()), true)
{
    return true;
}

template <typename>
constexpr auto can_call_mem_swap_impl(...) noexcept -> bool
{
    return false;
}

template <typename O>
constexpr auto can_call_mem_swap() noexcept -> bool
{
    return can_call_mem_swap_impl<O>(0);
}

struct not_swappable_not_move_assignable
{
    auto operator=(not_swappable_not_move_assignable&&) -> not_swappable_not_move_assignable&
        = delete;
};
auto swap(not_swappable_not_move_assignable&, not_swappable_not_move_assignable&) -> void = delete;

template <typename O, typename Expected>
constexpr auto check_value_type() noexcept -> void
{
    using O_C = O const;
    using O_V = O volatile;
    using O_CV = O const volatile;
    
    static_assert(bml::is_same_v<typename O::value_type, Expected>);
    static_assert(bml::is_same_v<typename O_C::value_type, Expected>);
    static_assert(bml::is_same_v<typename O_V::value_type, Expected>);
    static_assert(bml::is_same_v<typename O_CV::value_type, Expected>);
}

auto test_main() noexcept -> int
{
    // Check that a default-constructed optional does not hold a value.
    {
        constexpr auto o = bml::optional<int>();
        static_assert(!o.has_value());
    }
    
    // Check that an optional constructed via the nullopt constructor does not hold a value.
    {
        constexpr auto o = bml::optional<int>(bml::nullopt);
        static_assert(!o.has_value());
    }
    
    // Check that an optional holding a value can be constructed via the in_place constructor.
    {
        constexpr auto o1 = bml::optional<int>(bml::in_place, 42);
        static_assert(o1.has_value());
        static_assert(o1.value() == 42);
        
        constexpr auto o2 = bml::optional<multiply>(bml::in_place, 5, 10);
        static_assert(o2.has_value());
        static_assert(o2.value().value == 50);
    }
    
    // Check that the in_place constructor is marked explicit.
    {
        static_assert(bml::is_explicitly_constructible_v<bml::optional<int>,
            bml::in_place_ty, int>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<int>,
            bml::in_place_ty>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<int const>,
            bml::in_place_ty>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<int const volatile>,
            bml::in_place_ty, int const&>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<int*>,
            bml::in_place_ty>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<multiply>,
            bml::in_place_ty, int&, int const&&>);
        static_assert(bml::is_explicitly_constructible_v<bml::optional<multiply const volatile>,
            bml::in_place_ty, int, int const volatile&>);
    }
    
    // Check that the in_place constructor is not callable if T is not constructible from the
    // provided arguments.
    {
        static_assert(!bml::is_constructible_v<bml::optional<void*>, bml::in_place_ty, int const*>);
        static_assert(!bml::is_constructible_v<bml::optional<multiply>, bml::in_place_ty>);
        static_assert(!bml::is_constructible_v<bml::optional<multiply>, bml::in_place_ty, int>);
        static_assert(!bml::is_constructible_v<bml::optional<multiply>, bml::in_place_ty, int,
            int*>);
    }
    
    // Check that optional can be copy-constructed if T is copy-constructible.
    {
        // Non-constexpr context
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(o1);
            
            bmltb_assert(!o2.has_value());
        }
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            auto o1 = bml::optional<int const volatile>(bml::in_place, 42);
            auto o2 = bml::optional<int const volatile>(o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            auto o1 = bml::optional<copy_ctor>(bml::in_place, 42);
            auto o2 = bml::optional<copy_ctor>(o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().copy_ctor_called);
        }
        {
            auto o1 = bml::optional<copy_ctor const volatile>(bml::in_place, 42);
            auto o2 = bml::optional<copy_ctor const volatile>(o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().copy_ctor_called);
        }
        {
            auto o1 = bml::optional<triv_copy_ctor>(bml::in_place, 42);
            auto o2 = bml::optional<triv_copy_ctor>(o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
        }
        
        // Constexpr context (only available when copy constructors are trivial; non-triviality
        // requires placement new to be emitted)
        {
            constexpr auto o1 = bml::optional<int>(bml::nullopt);
            constexpr auto o2 = bml::optional<int>(o1);
            
            static_assert(!o2.has_value());
        }
        {
            constexpr auto o1 = bml::optional<int>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<int>(o1);
            
            static_assert(o2.has_value());
            static_assert(o2.value() == 42);
        }
        {
            constexpr auto o1 = bml::optional<int const>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<int const>(o1);
            
            static_assert(o2.has_value());
            static_assert(o2.value() == 42);
        }
        {
            constexpr auto o1 = bml::optional<triv_copy_ctor>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<triv_copy_ctor>(o1);
            
            static_assert(o2.has_value());
            static_assert(o2.value().value == 42);
        }
        {
            constexpr auto o1 = bml::optional<triv_copy_ctor const>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<triv_copy_ctor const>(o1);
            
            static_assert(o2.has_value());
            static_assert(o2.value().value == 42);
        }
    }
    
    // Check that optional cannot be copy-constructed if T is not copy-constructible.
    {
        static_assert(!bml::is_copy_constructible_v<bml::optional<no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::optional<implicit_no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::optional<triv_copy_ctor const volatile>>);
    }
    
    // Check that optional is trivially copy-constructible if T is trivially copy-constructible.
    {
        static_assert(bml::is_trivially_copy_constructible_v<bml::optional<int>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::optional<int const volatile>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::optional<triv_copy_ctor>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::optional<triv_copy_ctor const>>);
        
        static_assert(!bml::is_trivially_copy_constructible_v<bml::optional<copy_ctor>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::optional<copy_ctor volatile>>);
    }
    
    // Check that optional can be copy-assigned if T is both copy-assignable and copy-constructible.
    {
        // Non-constexpr context, both assigner and assignee empty.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign>(bml::nullopt);
            auto o2 = bml::optional<copy_assign>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign volatile>(bml::nullopt);
            auto o2 = bml::optional<copy_assign volatile>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        
        // Non-constexpr context, assignee empty.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign>(bml::in_place, 42);
            auto o2 = bml::optional<copy_assign>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(&ref == &o2);
            
            // Should be emplaced via copy construction, not assigned.
            bmltb_assert(!o2.value().copy_assign_called);
        }
        {
            auto o1 = bml::optional<copy_assign volatile>(bml::in_place, 42);
            auto o2 = bml::optional<copy_assign volatile>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(&ref == &o2);
            
            // Should be emplaced via copy construction, not assigned.
            bmltb_assert(!o2.value().copy_assign_called);
        }
        
        // Non-constexpr context, assigner empty.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign>(bml::nullopt);
            auto o2 = bml::optional<copy_assign>(bml::in_place, 42);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign volatile>(bml::nullopt);
            auto o2 = bml::optional<copy_assign volatile>(bml::in_place, 42);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        
        // Non-constexpr context, both assigner and assignee not empty.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::in_place, 20);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign>(bml::in_place, 42);
            auto o2 = bml::optional<copy_assign>(bml::in_place, 20);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().copy_assign_called);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<copy_assign volatile>(bml::in_place, 42);
            auto o2 = bml::optional<copy_assign volatile>(bml::in_place, 20);
            
            auto&& ref = (o2 = o1);
            
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().copy_assign_called);
            bmltb_assert(&ref == &o2);
        }
        
        // Constexpr context, both assigner and assignee empty (only available when T has trivial
        // copy assignments, copy constructors and destructors; non-triviality requires placement
        // new to be emitted).
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_copy_assign>(bml::nullopt);
            auto o2 = bml::optional<triv_copy_assign>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        // Constexpr context, assignee empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && o2.has_value() && o2.value() == 42;
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_copy_assign>(bml::in_place, 42);
            auto o2 = bml::optional<triv_copy_assign>(bml::nullopt);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && o2.has_value() && o2.value().value == 42;
        }());
        
        // Constexpr context, assigner empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_copy_assign>(bml::nullopt);
            auto o2 = bml::optional<triv_copy_assign>(bml::in_place, 42);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        // Non-constexpr context, both assigner and assignee not empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::in_place, 20);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && o2.has_value() && o2.value() == 42;
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_copy_assign>(bml::in_place, 42);
            auto o2 = bml::optional<triv_copy_assign>(bml::in_place, 20);
            
            auto&& ref = (o2 = o1);
            
            return (&ref == &o2) && o2.has_value() && o2.value().value == 42;
        }());
    }
    
    // Check that optional is not copy-assignable if T is not copy-assignable or not
    // copy-constructible.
    {
        static_assert(!bml::is_copy_assignable_v<bml::optional<int const>>);
        static_assert(!bml::is_copy_assignable_v<bml::optional<copy_assign const>>);
        static_assert(!bml::is_copy_assignable_v<bml::optional<no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::optional<implicit_no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::optional<no_copy_ctor>>);
    }
    
    // Check that optional's copy assignment is trivial if T's copy assignment, copy constructor and
    // destructor are trivial.
    {
        static_assert(bml::is_trivially_copy_assignable_v<bml::optional<int>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::optional<int volatile>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::optional<triv_copy_assign>>);
        
        static_assert(!bml::is_trivially_copy_assignable_v<bml::optional<copy_assign>>);
        static_assert(!bml::is_trivially_copy_assignable_v<bml::optional<dtor>>);
    }
    
    // Check that optional can be move-constructed if T is move-constructible, and that a moved-from
    // optional still has a value if it originally had a value.
    {
        // Non-constexpr context.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::move(o1));
            
            bmltb_assert(!o2.has_value());
        }
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            auto o1 = bml::optional<int const volatile>(bml::in_place, 42);
            auto o2 = bml::optional<int const volatile>(bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            auto o1 = bml::optional<move_ctor>(bml::in_place, 42);
            auto o2 = bml::optional<move_ctor>(bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().move_ctor_called);
        }
        {
            auto o1 = bml::optional<move_ctor volatile>(bml::in_place, 42);
            auto o2 = bml::optional<move_ctor volatile>(bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().move_ctor_called);
        }
        {
            auto o1 = bml::optional<triv_move_ctor>(bml::in_place, 42);
            auto o2 = bml::optional<triv_move_ctor>(bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
        }
        
        // Constexpr context (only available when move constructors are trivial; non-triviality
        // requires placement new to be emitted)
        {
            constexpr auto o1 = bml::optional<int>(bml::nullopt);
            constexpr auto o2 = bml::optional<int>(bml::move(o1));
            
            static_assert(!o2.has_value());
        }
        {
            constexpr auto o1 = bml::optional<int>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<int>(bml::move(o1));
            
            static_assert(o1.has_value());
            static_assert(o2.has_value());
            static_assert(o2.value() == 42);
        }
        {
            constexpr auto o1 = bml::optional<int const>(bml::in_place, 42);
            constexpr auto o2 = bml::optional<int const>(bml::move(o1));
            
            static_assert(o1.has_value());
            static_assert(o2.has_value());
            static_assert(o2.value() == 42);
        }
        
        // Move constructors cannot bind to const, so testing for move construction when T is a
        // class type needs to be done through constexpr functions instead of though declaring
        // constexpr variants and moving them around.
        static_assert([]()
        {
            auto o1 = bml::optional<triv_move_ctor>(bml::in_place, 42);
            auto o2 = bml::optional<triv_move_ctor>(bml::move(o1));
            
            return o1.has_value() && o2.has_value() && o2.value().value == 42;
        }());
    }
    
    // Check that optional's move-constructor does not participate in overload resolution if T is
    // not move-constructible.
    {
        // "Move-constructible" since the optional is still copy-constructible - overload resolution
        // selects the copy constructor.
        static_assert(bml::is_move_constructible_v<bml::optional<copy_ctor_no_move_ctor>>);
        
        // Not move-constructible since T is both not move-constructible and not copy-constructible.
        static_assert(!bml::is_move_constructible_v<bml::optional<no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::optional<implicit_no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::optional<triv_move_ctor const>>);
    }
    
    // Check that optional is trivially move-constructible if T is trivially move-constructible.
    {
        static_assert(bml::is_trivially_move_constructible_v<bml::optional<int>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::optional<int const volatile>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::optional<triv_move_ctor>>);
        
        static_assert(!bml::is_trivially_copy_constructible_v<bml::optional<move_ctor>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::optional<move_ctor volatile>>);
    }
    
    // Check that optional can be move-assigned if T is both move-assignable and move-constructible,
    // and that a moved-from optional still has a value if it originally had a value.
    {
        // Non-constexpr context, both assigner and assignee empty.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign>(bml::nullopt);
            auto o2 = bml::optional<move_assign>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign volatile>(bml::nullopt);
            auto o2 = bml::optional<move_assign volatile>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        
        // Non-constexpr context, assignee empty.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign>(bml::in_place, 42);
            auto o2 = bml::optional<move_assign>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(&ref == &o2);
            
            // Should be emplaced via move construction, not assigned.
            bmltb_assert(!o2.value().move_assign_called);
        }
        {
            auto o1 = bml::optional<move_assign volatile>(bml::in_place, 42);
            auto o2 = bml::optional<move_assign volatile>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(&ref == &o2);
            
            // Should be emplaced via move construction, not assigned.
            bmltb_assert(!o2.value().move_assign_called);
        }
        
        // Non-constexpr context, assigner empty.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign>(bml::nullopt);
            auto o2 = bml::optional<move_assign>(bml::in_place, 42);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign volatile>(bml::nullopt);
            auto o2 = bml::optional<move_assign volatile>(bml::in_place, 42);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(!o2.has_value());
            bmltb_assert(&ref == &o2);
        }
        
        // Non-constexpr context, both assigner and assignee not empty.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::in_place, 20);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign>(bml::in_place, 42);
            auto o2 = bml::optional<move_assign>(bml::in_place, 20);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().move_assign_called);
            bmltb_assert(&ref == &o2);
        }
        {
            auto o1 = bml::optional<move_assign volatile>(bml::in_place, 42);
            auto o2 = bml::optional<move_assign volatile>(bml::in_place, 20);
            
            auto&& ref = (o2 = bml::move(o1));
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
            bmltb_assert(o2.value().move_assign_called);
            bmltb_assert(&ref == &o2);
        }
        
        // Constexpr context, both assigner and assignee empty (only available when T has trivial
        // move assignments, move constructors and destructors; non-triviality requires placement
        // new to be emitted).
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_move_assign>(bml::nullopt);
            auto o2 = bml::optional<triv_move_assign>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        // Constexpr context, assignee empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && o1.has_value() && o2.has_value() && o2.value() == 42;
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_move_assign>(bml::in_place, 42);
            auto o2 = bml::optional<triv_move_assign>(bml::nullopt);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && o1.has_value() && o2.has_value() && o2.value().value == 42;
        }());
        
        // Constexpr context, assigner empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_move_assign>(bml::nullopt);
            auto o2 = bml::optional<triv_move_assign>(bml::in_place, 42);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && !o2.has_value();
        }());
        
        // Non-constexpr context, both assigner and assignee not empty.
        static_assert([]()
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::in_place, 20);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && o1.has_value() && o2.has_value() && o2.value() == 42;
        }());
        
        static_assert([]()
        {
            auto o1 = bml::optional<triv_move_assign>(bml::in_place, 42);
            auto o2 = bml::optional<triv_move_assign>(bml::in_place, 20);
            
            auto&& ref = (o2 = bml::move(o1));
            
            return (&ref == &o2) && o1.has_value() && o2.has_value() && o2.value().value == 42;
        }());
    }
    
    // Check that optional's move-assignment does not participate in overload resolution if T is
    // not move-assignable or not move-constructible.
    {
        // "Move-assignable" since the T is still copy-assignable - overload resolution selects move
        // assignment operator.
        static_assert(bml::is_move_assignable_v<bml::optional<copyable_no_move_assign>>);
        
        // Not move-assignable since the T is both not move-assignable and not move-constructible.
        static_assert(!bml::is_move_assignable_v<bml::optional<int const>>);
        static_assert(!bml::is_move_assignable_v<bml::optional<no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::optional<implicit_no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::optional<triv_move_assign const>>);
    }
    
    // Check that optional's move assignment is trivial if T's move assignment, move constructor and
    // destructor are trivial.
    {
        static_assert(bml::is_trivially_move_assignable_v<bml::optional<int>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::optional<int volatile>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::optional<triv_move_assign>>);
        
        static_assert(!bml::is_trivially_move_assignable_v<bml::optional<move_assign>>);
        static_assert(!bml::is_trivially_move_assignable_v<bml::optional<dtor>>);
    }
    
    // Check that T's destructor is only invoked when the containing optional is destroyed or has
    // its value removed via methods such as a reset call, assignment with nullopt etc.
    {
        // Check that destructor is called after going out of scope.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::in_place);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that destructor is not called during copy construction.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            {
                auto o2 = bml::optional<dtor>(o1);
                bmltb_assert(dtor::count == 0);
            }
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that destructor is not called during move construction.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            {
                auto o2 = bml::optional<dtor>(bml::move(o1));
                bmltb_assert(dtor::count == 0);
            }
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that neither the assignee's nor assigner's destructors are called on copy
        // assignment when both do not hold values.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::nullopt);
            auto o2 = bml::optional<dtor>(bml::nullopt);
            
            o2 = o1;
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 0);
        
        // Check that assignee's destructor is called on copy assignment when the assignee holds a
        // value, but the assigner does not.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::nullopt);
            auto o2 = bml::optional<dtor>(bml::in_place);
            
            o2 = o1;
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that assigner's destructor is not called on copy assignment when the assignee does
        // not hold a value, but the assigner does.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            auto o2 = bml::optional<dtor>(bml::nullopt);
            
            o2 = o1;
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that neither the assignee's nor assigner's destructors are called on copy
        // assignment when both the assigner and assignee hold values.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            auto o2 = bml::optional<dtor>(bml::in_place);
            
            o2 = o1;
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that neither the assignee's nor assigner's destructors are called on move
        // assignment when both do not hold values.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::nullopt);
            auto o2 = bml::optional<dtor>(bml::nullopt);
            
            o2 = bml::move(o1);
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 0);
        
        // Check that assignee's destructor is called on move assignment when the assignee holds a
        // value, but the assigner does not.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::nullopt);
            auto o2 = bml::optional<dtor>(bml::in_place);
            
            o2 = bml::move(o1);
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that assigner's destructor is not called on move assignment when the assignee does
        // not hold a value, but the assigner does.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            auto o2 = bml::optional<dtor>(bml::nullopt);
            
            o2 = bml::move(o1);
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that neither the assignee's nor assigner's destructors are called on move
        // assignment when both the assigner and assignee hold values.
        dtor::count = 0;
        {
            auto o1 = bml::optional<dtor>(bml::in_place);
            auto o2 = bml::optional<dtor>(bml::in_place);
            
            o2 = bml::move(o1);
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that the destructor is called when a value is emplaced into an optional that
        // already holds a value.
        dtor::count = 0;
        {
           auto o = bml::optional<dtor>(bml::in_place);
           o.emplace();
           
           bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 2);
        
        // Check that the destructor is not called when a value is emplaced into an optional that
        // does not hold a value.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::nullopt);
            o.emplace();
            
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that the destructor is called when an optional that holds a value is reset.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::in_place);
            o.reset();
            
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that the destructor is not called when an optional that does not hold a value is
        // reset.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::nullopt);
            o.reset();
            
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 0);
        
        // Check that the destructor is called when nullopt is assigned to an optional that holds a
        // value.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::in_place);
            o = bml::nullopt;
            
            bmltb_assert(dtor::count == 1);
        }
        bmltb_assert(dtor::count == 1);
        
        // Check that the destructor is not called when nullopt is assigned to an optional that does
        // not hold a value.
        dtor::count = 0;
        {
            auto o = bml::optional<dtor>(bml::nullopt);
            o = bml::nullopt;
            
            bmltb_assert(dtor::count == 0);
        }
        bmltb_assert(dtor::count == 0);
    }
    
    // Check that optional is not destructible if T is not destructible.
    {
        static_assert(!bml::is_destructible_v<bml::optional<no_dtor>>);
        static_assert(!bml::is_destructible_v<bml::optional<no_dtor const>>);
        static_assert(!bml::is_destructible_v<bml::optional<no_dtor volatile>>);
        static_assert(!bml::is_destructible_v<bml::optional<no_dtor const volatile>>);
    }
    
    // Check that optional's destructor is trivial if T's destructor is trivial.
    {
        static_assert(bml::is_trivially_destructible_v<bml::optional<int>>);
        static_assert(bml::is_trivially_destructible_v<bml::optional<int const volatile>>);
        static_assert(bml::is_trivially_destructible_v<bml::optional<triv_dtor>>);
        static_assert(bml::is_trivially_destructible_v<bml::optional<triv_dtor const volatile>>);
        
        static_assert(!bml::is_trivially_destructible_v<bml::optional<dtor>>);
    }
    
    // Check that the value member function and the indirection operator both return a reference to
    // the stored value that is of the appropriate type for the optional's value category (i.e.
    // lvalue reference if the optional is an lvalue, rvalue reference otherwise), with the
    // optional's const qualification applied to T.
    {
        // Check return type.
        check_value_fn_and_indir_op_type<bml::optional<int>, int>();
        check_value_fn_and_indir_op_type<bml::optional<double const>, double const>();
        check_value_fn_and_indir_op_type<bml::optional<copy_ctor volatile>, copy_ctor volatile>();
        check_value_fn_and_indir_op_type<bml::optional<int const**>, int const**>();
        
        // Check that correct reference is returned.
        static_assert([]
        {
            auto o = bml::optional<bool>(bml::in_place, true);
            return o.value();
        }());
        
        static_assert([]
        {
            auto o = bml::optional<bool>(bml::in_place, true);
            return *o;
        }());
        
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            return o.value().value == 50;
        }());
        
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            o.value().value = 42;
            
            return o.value().value == 42;
        }());
        
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            return (*o).value == 50;
        }());
        
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            (*o).value = 42;
            
            return (*o).value == 42;
        }());
    }
    
    // Check that the member-of-pointer operator returns a pointer to the stored value, with the
    // optional's const qualification applied to T.
    {
        // Check return type.
        check_mem_of_ptr_op_type<bml::optional<int>, int>();
        check_mem_of_ptr_op_type<bml::optional<double const>, double const>();
        check_mem_of_ptr_op_type<bml::optional<copy_ctor volatile>, copy_ctor volatile>();
        check_mem_of_ptr_op_type<bml::optional<int const**>, int const**>();
        
        // Check that correct pointer is returned.
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            return o->value == 50;
        }());
        
        static_assert([]
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            o->value = 42;
            
            return o->value == 42;
        }());
    }
    
    // Check that has_value and bool conversion correctly reflect whether the optional is holding a
    // value.
    {
        // Holding no value.
        {
            constexpr auto o = bml::optional<int>(bml::nullopt);
        
            static_assert(!o.has_value());
            static_assert(!static_cast<bool>(o));
        }
        
        // Holding a value.
        {
            constexpr auto o = bml::optional<int>(bml::in_place, 42);
        
            static_assert(o.has_value());
            static_assert(static_cast<bool>(o));
        }
    }
    
    // Check that optional is not implicitly convertible to bool.
    {
        static_assert(!bml::is_convertible_v<bml::optional<int>, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<int const volatile>, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<int> const volatile, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<int const volatile> const volatile,
            bool>);
        
        static_assert(!bml::is_convertible_v<bml::optional<multiply>, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<multiply const volatile>, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<multiply> const volatile, bool>);
        static_assert(!bml::is_convertible_v<bml::optional<multiply const volatile> const volatile,
            bool>);
    }
    
    // Check that emplace constructs a new value in-place.
    {
        // Emplace into empty optional.
        {
            auto o = bml::optional<int>(bml::nullopt);
            o.emplace(42);
            
            bmltb_assert(o.has_value());
            bmltb_assert(o.value() == 42);
        }
        {
            auto o = bml::optional<multiply>(bml::nullopt);
            o.emplace(5, 10);
            
            bmltb_assert(o.has_value());
            bmltb_assert(o.value().value == 50);
        }
        
        // Emplace into optional holding a value.
        {
            auto o = bml::optional<int>(bml::in_place, 100);
            o.emplace(42);
            
            bmltb_assert(o.value() == 42);
        }
        {
            auto o = bml::optional<multiply>(bml::in_place, 5, 10);
            o.emplace(4, 20);
            
            bmltb_assert(o.value().value == 80);
        }
    }
    
    // Check that emplace is not callable if T is not constructible from emplace's arguments.
    {
        static_assert(!can_call_emplace<bml::optional<void*>, int const*>());
        static_assert(!can_call_emplace<bml::optional<int>, int, int>());
        static_assert(!can_call_emplace<bml::optional<multiply>>());
        static_assert(!can_call_emplace<bml::optional<multiply>, int>());
        static_assert(!can_call_emplace<bml::optional<multiply>, copy_ctor>());
    }
    
    // Check that an optional does not have a value after calling reset on it.
    {
        // Resetting an optional that does not hold a value.
        {
            auto o = bml::optional<int>(bml::nullopt);
            o.reset();
            
            bmltb_assert(!o.has_value());
        }
        
        // Resetting an optional that holds a value.
        {
            auto o = bml::optional<int>(bml::in_place, 42);
            o.reset();
            
            bmltb_assert(!o.has_value());
        }
    }
    
    // Check that an optional does not have a value after nullopt has been assigned to it.
    {
        // Assigning to an optional that does not hold a value.
        {
            auto o = bml::optional<int>(bml::nullopt);
            o = bml::nullopt;
            
            bmltb_assert(!o.has_value());
        }
        
        // Assigning to an optional that holds a value.
        {
            auto o = bml::optional<int>(bml::in_place, 42);
            o = bml::nullopt;
            
            bmltb_assert(!o.has_value());
        }
    }
    
    // Check that member swap swaps the optional's currently held value (or lack thereof) with the
    // argument optional's value (or lack thereof).
    {
        // Both the current and argument optionals hold values.
        {
            auto o1 = bml::optional<int>(bml::in_place, 500);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            o1.swap(o2);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o1.value() == 42);
            bmltb_assert(o2.value() == 500);
        }
        {
            // Check that this calls the user-defined swap if it's available.
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::in_place, 500);
            auto o2 = bml::optional<swappee>(bml::in_place, 42);
            
            o1.swap(o2);
            
            bmltb_assert(swappee::swap_called);
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o1.value().value == 42);
            bmltb_assert(o2.value().value == 500);
        }
        
        // Current optional does not hold a value, but the argument optional does.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            o1.swap(o2);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o1.value() == 42);
            bmltb_assert(!o2.has_value());
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::nullopt);
            auto o2 = bml::optional<swappee>(bml::in_place, 42);
            
            o1.swap(o2);
            
            // Should be move-constructed, not swapped.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o1.value().value == 42);
            bmltb_assert(!o2.has_value());
        }
        
        // Current optional holds a value, but the argument optional does not.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            o1.swap(o2);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::in_place, 42);
            auto o2 = bml::optional<swappee>(bml::nullopt);
            
            o1.swap(o2);
            
            // Should be move-constructed, not swapped.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
        }
        
        // Both the current and argument optionals do not hold values.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            o1.swap(o2);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(!o2.has_value());
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::nullopt);
            auto o2 = bml::optional<swappee>(bml::nullopt);
            
            o1.swap(o2);
            
            bmltb_assert(!swappee::swap_called);
            bmltb_assert(!o1.has_value());
            bmltb_assert(!o2.has_value());
        }
    }
    
    // Check that member swap is not callable if T is not swappable or not move-constructible.
    {
        static_assert(!can_call_mem_swap<bml::optional<no_move_ctor>>());
        static_assert(!can_call_mem_swap<bml::optional<not_swappable>>());
    }
    
    // Check that free swap swaps the optional's currently held value (or lack thereof) with the
    // argument optional's value (or lack thereof).
    {
        // Both the current and argument optionals hold values.
        {
            auto o1 = bml::optional<int>(bml::in_place, 500);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o1.value() == 42);
            bmltb_assert(o2.value() == 500);
        }
        {
            // Check that this calls the user-defined swap if it's available.
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::in_place, 500);
            auto o2 = bml::optional<swappee>(bml::in_place, 42);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(swappee::swap_called);
            bmltb_assert(o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o1.value().value == 42);
            bmltb_assert(o2.value().value == 500);
        }
        
        // Current optional does not hold a value, but the argument optional does.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::in_place, 42);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o1.value() == 42);
            bmltb_assert(!o2.has_value());
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::nullopt);
            auto o2 = bml::optional<swappee>(bml::in_place, 42);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            // Should be move-constructed, not swapped.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(o1.has_value());
            bmltb_assert(o1.value().value == 42);
            bmltb_assert(!o2.has_value());
        }
        
        // Current optional holds a value, but the argument optional does not.
        {
            auto o1 = bml::optional<int>(bml::in_place, 42);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value() == 42);
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::in_place, 42);
            auto o2 = bml::optional<swappee>(bml::nullopt);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            // Should be move-constructed, not swapped.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(o2.has_value());
            bmltb_assert(o2.value().value == 42);
        }
        
        // Both the current and argument optionals do not hold values.
        {
            auto o1 = bml::optional<int>(bml::nullopt);
            auto o2 = bml::optional<int>(bml::nullopt);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(!o1.has_value());
            bmltb_assert(!o2.has_value());
        }
        {
            swappee::swap_called = false;
            
            auto o1 = bml::optional<swappee>(bml::nullopt);
            auto o2 = bml::optional<swappee>(bml::nullopt);
            
            using bml::swap;
            using ::swap;
            swap(o1, o2);
            
            bmltb_assert(!swappee::swap_called);
            bmltb_assert(!o1.has_value());
            bmltb_assert(!o2.has_value());
        }
    }
    
    // Check that free swap is not callable if T is not swappable or not move-constructible, and the
    // optional itself is not move-constructible or move-assignable (so that the "generic" swap
    // cannot be used).
    {
        static_assert(!bml::is_swappable_v<bml::optional<no_move_ctor>>);
        static_assert(!bml::is_swappable_v<bml::optional<not_swappable_not_move_assignable>>);
    }
    
    // Check that the value_type member typedef names T.
    {
        check_value_type<bml::optional<int>, int>();
        check_value_type<bml::optional<int const>, int const>();
        check_value_type<bml::optional<int volatile>, int volatile>();
        check_value_type<bml::optional<int const volatile>, int const volatile>();
        
        check_value_type<bml::optional<multiply>, multiply>();
        check_value_type<bml::optional<multiply const volatile>, multiply const volatile>();
    }
    
    // Check that nullopt_ty is not an aggregate and cannot be default-constructed.
    {
        static_assert(!bml::is_aggregate_v<bml::nullopt_ty>);
        static_assert(!bml::is_default_constructible_v<bml::nullopt_ty>);
    }
    
    return 0;
}
