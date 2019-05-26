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
#include <bml/containers/variant.hpp>
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
#include <bml/type_traits/is_same.hpp>
#include <bml/type_traits/is_swappable.hpp>
#include <bml/utilities/declval.hpp>

template <typename... Ts> struct overload : Ts... { using Ts::operator()...; };
template <typename... Ts> overload(Ts...) -> overload<Ts...>;

struct ctor
{
    int value;
    
    constexpr explicit ctor(int i) : value(i) {};
};

struct trivial {};

struct multiply
{
    int value;
    
    constexpr multiply(int a, int b) : value(a * b) {};
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
    
    // variant needs copy-constructibility for copy-assignment.
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
    
    // variant needs copy-constructibility for copy-assignment.
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
    
    // variant needs move-constructibility for move-assignment.
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
    
    // variant needs move-constructibility for move-assignment.
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

struct dtor_1
{
    inline static auto count = 0;
    
    dtor_1() = default;
    ~dtor_1() { ++count; }
    
    dtor_1(dtor_1 const&) = default;
    dtor_1(dtor_1&&) = default;
    auto operator=(dtor_1 const&) -> dtor_1& = default;
    auto operator=(dtor_1&&) -> dtor_1& = default;
};

struct dtor_2
{
    inline static auto count = 0;
    
    dtor_2() = default;
    ~dtor_2() { ++count; }
    
    dtor_2(dtor_2 const&) = default;
    dtor_2(dtor_2&&) = default;
    auto operator=(dtor_2 const&) -> dtor_2& = default;
    auto operator=(dtor_2&&) -> dtor_2& = default;
};

struct no_dtor
{
    ~no_dtor() = delete;
};

template <::ptrdiff_t I, typename V, typename Expected>
constexpr auto check_variant_alternative() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::variant_alternative<I, V>::type, Expected>);
    static_assert(bml::is_same_v<bml::variant_alternative_ty<I, V>, Expected>);
    
    static_assert(bml::is_same_v<typename bml::variant_alternative<I, V const>::type,
        Expected const>);
    static_assert(bml::is_same_v<bml::variant_alternative_ty<I, V const>,
        Expected const>);
    
    static_assert(bml::is_same_v<typename bml::variant_alternative<I, V volatile>::type,
        Expected volatile>);
    static_assert(bml::is_same_v<bml::variant_alternative_ty<I, V volatile>,
        Expected volatile>);
    
    static_assert(bml::is_same_v<typename bml::variant_alternative<I, V const volatile>::type,
        Expected const volatile>);
    static_assert(bml::is_same_v<bml::variant_alternative_ty<I, V const volatile>,
        Expected const volatile>);
}

template <typename V, ::ptrdiff_t N>
constexpr auto check_variant_size() noexcept -> void
{
    static_assert(bml::variant_size<V>::value == N);
    static_assert(bml::variant_size_v<V> == N);
    
    static_assert(bml::variant_size<V const>::value == N);
    static_assert(bml::variant_size_v<V const> == N);
    
    static_assert(bml::variant_size<V volatile>::value == N);
    static_assert(bml::variant_size_v<V volatile> == N);
    
    static_assert(bml::variant_size<V const volatile>::value == N);
    static_assert(bml::variant_size_v<V const volatile> == N);
}

template <typename V, ::ptrdiff_t I, typename Expected>
constexpr auto check_member_get_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::declval<V&>().template get<I>()),
        Expected&>);
    static_assert(bml::is_same_v<decltype(bml::declval<V const&>().template get<I>()),
        Expected const&>);
    
    static_assert(bml::is_same_v<decltype(bml::declval<V>().template get<I>()),
        Expected&&>);
    static_assert(bml::is_same_v<decltype(bml::declval<V const>().template get<I>()),
        Expected const&&>);
}

template <typename V, ::ptrdiff_t I, typename Expected>
constexpr auto check_free_get_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<V&>())),
        Expected&>);
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<V const&>())),
        Expected const&>);
    
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<V>())),
        Expected&&>);
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<V const>())),
        Expected const&&>);
}

struct visit_sniffer
{
    template <typename...>
    class result
    {
    private:
    
        inline static char marker;
        
    public:
    
        static auto id() noexcept -> void* { return static_cast<void*>(&marker); }
        
    };

    struct lvalue {};
    struct rvalue {};
    struct const_lvalue {};
    struct const_rvalue {};
    
    template <typename... Args>
    auto operator()(Args&&...) & noexcept -> void*
    {
        return result<lvalue, Args&&...>::id();
    }
    
    template <typename... Args>
    auto operator()(Args&&...) && noexcept -> void*
    {
        return result<rvalue, Args&&...>::id();
    }
    
    template <typename... Args>
    auto operator()(Args&&...) const & noexcept -> void*
    {
        return result<const_lvalue, Args&&...>::id();
    }
    
    template <typename... Args>
    auto operator()(Args&&...) const && noexcept -> void*
    {
        return result<const_rvalue, Args&&...>::id();
    }
};

template <typename... Ts>
constexpr auto visit(Ts&&...) noexcept -> int { return 100; }

template <typename V, ::ptrdiff_t I, typename... Args>
constexpr auto can_call_emplace_impl(int) noexcept
    -> decltype(bml::declval<V>().template emplace<I>(bml::declval<Args>()...), true)
{
    return true;
}

template <typename, ::ptrdiff_t, typename...>
constexpr auto can_call_emplace_impl(...) noexcept -> bool
{
    return false;
}

template <typename V, ::ptrdiff_t I, typename... Args>
constexpr auto can_call_emplace() noexcept -> bool
{
    return can_call_emplace_impl<V, I, Args...>(0);
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

template <typename V>
constexpr auto can_call_mem_swap_impl(int) noexcept
    -> decltype(bml::declval<V>().template swap(bml::declval<V&>()), true)
{
    return true;
}

template <typename>
constexpr auto can_call_mem_swap_impl(...) noexcept -> bool
{
    return false;
}

template <typename V>
constexpr auto can_call_mem_swap() noexcept -> bool
{
    return can_call_mem_swap_impl<V>(0);
}

auto test_main() noexcept -> int
{
    // Check that alternatives can be constructed by index via in_place_index.
    {
        // Non-constexpr context.
        {
            auto v = bml::variant<int>(bml::in_place_index<0>, 42);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>() == 42);
        }
        {
            auto v = bml::variant<int>(bml::in_place_index<0>);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>() == 0);
        }
        {
            auto v = bml::variant<ctor>(bml::in_place_index<0>, 42);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>().value == 42);
        }
        {
            auto v = bml::variant<multiply>(bml::in_place_index<0>, 10, 5);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>().value == 50);
        }
        {
            auto v = bml::variant<int, double>(bml::in_place_index<0>, 100);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>() == 100);
        }
        {
            auto v = bml::variant<int, double>(bml::in_place_index<1>, 100.5);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 100.5);
        }
        {
            auto v = bml::variant<int, int, int>(bml::in_place_index<1>, 42);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 42);
        }
        {
            auto v = bml::variant<int, int const, int volatile>(bml::in_place_index<1>, 42);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 42);
        }
        {
            auto v = bml::variant<int, double volatile, ctor const>(bml::in_place_index<1>, 42.5);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 42.5);
        }
        {
            auto v = bml::variant<int, multiply volatile, ctor>(bml::in_place_index<1>, 10, 5);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>().value == 50);
        }
        {
            auto i = 42;
            auto v = bml::variant<double, ctor, int const>(bml::in_place_index<2>, i);
            bmltb_assert(v.index() == 2);
            bmltb_assert(v.get<2>() == 42);
        }
        {
            auto i = 5;
            auto j = 10;
            auto v = bml::variant<double, multiply, int const>(bml::in_place_index<1>, i, j);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>().value == 50);
        }
        
        // Constexpr context.
        {
            constexpr auto v = bml::variant<int>(bml::in_place_index<0>, 42);
            static_assert(v.index() == 0);
            static_assert(v.get<0>() == 42);
        }
        {
            constexpr auto v = bml::variant<int>(bml::in_place_index<0>);
            static_assert(v.index() == 0);
            static_assert(v.get<0>() == 0);
        }
        {
            constexpr auto v = bml::variant<ctor>(bml::in_place_index<0>, 42);
            static_assert(v.index() == 0);
            static_assert(v.get<0>().value == 42);
        }
        {
            constexpr auto v = bml::variant<multiply>(bml::in_place_index<0>, 10, 5);
            static_assert(v.index() == 0);
            static_assert(v.get<0>().value == 50);
        }
        {
            constexpr auto v = bml::variant<int, double>(bml::in_place_index<0>, 100);
            static_assert(v.index() == 0);
            static_assert(v.get<0>() == 100);
        }
        {
            constexpr auto v = bml::variant<int, double>(bml::in_place_index<1>, 100.5);
            static_assert(v.index() == 1);
            static_assert(v.get<1>() == 100.5);
        }
        {
            constexpr auto v = bml::variant<int, int, int>(bml::in_place_index<1>, 42);
            static_assert(v.index() == 1);
            static_assert(v.get<1>() == 42);
        }
        {
            constexpr auto v = bml::variant<int, int const, int>(bml::in_place_index<1>, 42);
            static_assert(v.index() == 1);
            static_assert(v.get<1>() == 42);
        }
        {
            constexpr auto v = bml::variant<int, double const, ctor const>(
                bml::in_place_index<1>, 42.5);
            static_assert(v.index() == 1);
            static_assert(v.get<1>() == 42.5);
        }
        {
            constexpr auto v = bml::variant<int, multiply const, ctor>(bml::in_place_index<1>, 10, 5);
            static_assert(v.index() == 1);
            static_assert(v.get<1>().value == 50);
        }
        {
            constexpr auto i = 42;
            constexpr auto v = bml::variant<double, ctor, int const>(bml::in_place_index<2>, i);
            static_assert(v.index() == 2);
            static_assert(v.get<2>() == 42);
        }
        {
            constexpr auto i = 5;
            constexpr auto j = 10;
            constexpr auto v = bml::variant<double, multiply, int const>(bml::in_place_index<1>,
                i, j);
            static_assert(v.index() == 1);
            static_assert(v.get<1>().value == 50);
        }
    }
    
    // Check that the constructor for constructing alternatives by index is marked explicit.
    {
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int>,
            bml::in_place_index_ty<0>, int>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int>,
            bml::in_place_index_ty<0>, int const volatile&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int>,
            bml::in_place_index_ty<0>>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int const>,
            bml::in_place_index_ty<0>, int>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int volatile>,
            bml::in_place_index_ty<0>, int&&>);
        
        static_assert(bml::is_explicitly_constructible_v<bml::variant<ctor>,
            bml::in_place_index_ty<0>, int>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<ctor const>,
            bml::in_place_index_ty<0>, int const&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<multiply>,
            bml::in_place_index_ty<0>, int const&, int const&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<multiply volatile>,
            bml::in_place_index_ty<0>, int&&, int const&&>);
        
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int, double>,
            bml::in_place_index_ty<0>, int>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int volatile, double>,
            bml::in_place_index_ty<0>, int const&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<ctor, multiply>,
            bml::in_place_index_ty<0>, int&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int, double>,
            bml::in_place_index_ty<1>, double>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int, double const>,
            bml::in_place_index_ty<1>, double&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<int, ctor>,
            bml::in_place_index_ty<1>, int const&>);
        static_assert(bml::is_explicitly_constructible_v<bml::variant<ctor, multiply>,
            bml::in_place_index_ty<1>, int&, int&>);
        
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, double volatile, ctor const>,
            bml::in_place_index_ty<0>, int const&>);
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, double volatile, ctor const>,
            bml::in_place_index_ty<0>>);
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, double volatile, ctor const>,
            bml::in_place_index_ty<1>, double>);
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, double volatile, ctor const>,
            bml::in_place_index_ty<1>, double&>);
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, double volatile, ctor const>,
            bml::in_place_index_ty<2>, int>);
        static_assert(bml::is_explicitly_constructible_v<
            bml::variant<int, ctor const, multiply const>,
            bml::in_place_index_ty<2>, int, int>);
    }
    
    // Check that the variant is not constructible by index if the alternative at that index is not
    // constructible from the provided arguments.
    {
        static_assert(!bml::is_constructible_v<bml::variant<void*>, bml::in_place_index_ty<0>,
            int const*>);
        static_assert(!bml::is_constructible_v<bml::variant<ctor>, bml::in_place_index_ty<0>>);
        static_assert(!bml::is_constructible_v<bml::variant<ctor>, bml::in_place_index_ty<0>,
            bmltb::union_type>);
        static_assert(!bml::is_constructible_v<bml::variant<ctor const volatile>,
            bml::in_place_index_ty<0>, bmltb::union_type>);
        static_assert(!bml::is_constructible_v<bml::variant<multiply>, bml::in_place_index_ty<0>,
            int>);
        static_assert(!bml::is_constructible_v<bml::variant<multiply>, bml::in_place_index_ty<0>,
            ctor>);
        
        static_assert(!bml::is_constructible_v<bml::variant<int, ctor>, bml::in_place_index_ty<1>>);
        static_assert(!bml::is_constructible_v<bml::variant<int, ctor>, bml::in_place_index_ty<1>,
            bmltb::union_type>);
        
        static_assert(!bml::is_constructible_v<bml::variant<int, multiply, ctor>,
            bml::in_place_index_ty<1>, int const&>);
    }
    
    // Check that the appropriate alternative's copy constructor is called when the variant is
    // constructed via copy construction.
    {
        // Non-constexpr context.
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(v1);
            
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(v1);
            
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(v1);
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double const volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double const volatile>(v1);
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, copy_ctor>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_ctor>(v1);
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().copy_ctor_called);
        }
        {
            auto v1 = bml::variant<int, copy_ctor const volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_ctor const volatile>(v1);
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().copy_ctor_called);
        }
        {
            auto v1 = bml::variant<int, triv_copy_ctor>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_copy_ctor>(v1);
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, triv_copy_ctor const, copy_ctor>(bml::in_place_index<2>,
                42);
            auto v2 = bml::variant<int, triv_copy_ctor const, copy_ctor>(v1);
            
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<2>().value == 42);
            bmltb_assert(v2.get<2>().copy_ctor_called);
        }
        
        // Constexpr context (only available when copy constructors are trivial; non-triviality
        // requires placement new to be emitted).
        {
            constexpr auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            constexpr auto v2 = bml::variant<int>(v1);
            
            static_assert(v2.index() == 0);
            static_assert(v2.get<0>() == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            constexpr auto v2 = bml::variant<int, double>(v1);
            
            static_assert(v2.index() == 0);
            static_assert(v2.get<0>() == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            constexpr auto v2 = bml::variant<int, double>(v1);
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>() == 42.5);
        }
        {
            constexpr auto v1 = bml::variant<int, double const>(bml::in_place_index<1>, 42.5);
            constexpr auto v2 = bml::variant<int, double const>(v1);
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>() == 42.5);
        }
        {
            constexpr auto v1 = bml::variant<int, triv_copy_ctor>(bml::in_place_index<1>, 42);
            constexpr auto v2 = bml::variant<int, triv_copy_ctor>(v1);
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>().value == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, triv_copy_ctor const>(bml::in_place_index<1>, 42);
            constexpr auto v2 = bml::variant<int, triv_copy_ctor const>(v1);
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>().value == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, trivial, triv_copy_ctor>(bml::in_place_index<2>,
                42);
            constexpr auto v2 = bml::variant<int, trivial, triv_copy_ctor>(v1);
            
            static_assert(v2.index() == 2);
            static_assert(v2.get<2>().value == 42);
        }
    }
    
    // Check that variant is not copy-constructible if any alternative is not copy-constructible.
    {
        static_assert(!bml::is_copy_constructible_v<bml::variant<no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<implicit_no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<trivial const volatile>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<no_copy_ctor const volatile>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<
            implicit_no_copy_ctor const volatile>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<copy_ctor, no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<copy_ctor,
            implicit_no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<copy_ctor const, double,
            no_copy_ctor volatile>>);
        static_assert(!bml::is_copy_constructible_v<bml::variant<copy_ctor volatile,
            implicit_no_copy_ctor const, int, double const>>);
    }
    
    // Check that variant's copy constructor is trivial if all alternatives' copy constructors are
    // trivial.
    {
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<trivial>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<triv_copy_ctor>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int const>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int, trivial>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int, triv_copy_ctor>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int, trivial,
            triv_copy_ctor const>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::variant<int, trivial const,
            triv_copy_ctor const>>);
        
        static_assert(!bml::is_trivially_copy_constructible_v<bml::variant<copy_ctor>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::variant<copy_ctor, int>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::variant<copy_ctor const volatile,
            int, trivial>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::variant<copy_ctor const, int,
            triv_copy_ctor const volatile>>);
    }
    
    // Check that the appropriate alternative's copy assignment operator is called when a variant
    // is copy assigned from another variant.
    {
        // Non-constexpr context, holding alternatives at the same index.
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 10.8);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double volatile>(bml::in_place_index<1>, 10.8);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().copy_assign_called);
        }
        {
            auto v1 = bml::variant<int, copy_assign volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_assign volatile>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().copy_assign_called);
        }
        {
            auto v1 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, copy_assign volatile, triv_copy_assign>(
                bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, copy_assign volatile, triv_copy_assign>(
                bml::in_place_index<2>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<2>().value == 42);
        }
        
        // Non-constexpr context, holding alternatives at different indices.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double volatile>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, copy_assign>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, copy_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            
            // Should be emplaced via copy construction, not copy assigned.
            bmltb_assert(!v2.get<1>().copy_assign_called);
        }
        {
            auto v1 = bml::variant<int, copy_assign volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, copy_assign volatile>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            
            // Should be emplaced via copy construction, not copy assigned.
            bmltb_assert(!v2.get<1>().copy_assign_called);
        }
        {
            auto v1 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_copy_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, copy_assign volatile, triv_copy_assign>(
                bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, copy_assign volatile, triv_copy_assign>(
                bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<1>().value == 42);
        }
        
        // Constexpr context, holding alternatives at the same index (only available when
        // alternatives' copy assignments, copy constructors and destructors are trivial;
        // non-triviality requires placement new to be emitted).
        static_assert([]()
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 10.5);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>() == 42.5;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>().value == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, trivial, triv_copy_assign>(bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, trivial, triv_copy_assign>(bml::in_place_index<2>, 10);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 2 && v2.get<2>().value == 42;
        }());
        
        // Constexpr context, holding alternatives at different indices (only available when
        // alternatives' copy assignments, copy constructors and destructors are trivial;
        // non-triviality requires placement new to be emitted).
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>() == 42.5;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, triv_copy_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_copy_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>().value == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, trivial, triv_copy_assign>(bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, trivial, triv_copy_assign>(bml::in_place_index<1>);
            
            auto&& ref = (v2 = v1);
            
            return (&ref == &v2) && v2.index() == 2 && v2.get<2>().value == 42;
        }());
    }
    
    // Check that variant is not copy-assignable if any alternative is not copy-assignable or not
    // copy-constructible.
    {
        static_assert(!bml::is_copy_assignable_v<bml::variant<int const>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<double, int const>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<copy_assign const volatile>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<implicit_no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<int, no_copy_assign,
            implicit_no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<int, no_copy_ctor>>);
        static_assert(!bml::is_copy_assignable_v<bml::variant<int, copy_assign, no_copy_ctor>>);
    }
    
    // Check that variant's copy assignment is trivial if all alternatives' copy assignments, copy
    // constructors and destructors are trivial.
    {
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<int>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<trivial>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<triv_copy_assign>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<int volatile, double>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<int volatile, trivial>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::variant<int, trivial,
            triv_copy_assign>>);
        
        static_assert(!bml::is_trivially_copy_assignable_v<bml::variant<copy_assign>>);
        static_assert(!bml::is_trivially_copy_assignable_v<bml::variant<copy_assign volatile>>);
        static_assert(!bml::is_trivially_copy_assignable_v<bml::variant<dtor_1>>);
        static_assert(!bml::is_trivially_copy_assignable_v<bml::variant<int const, trivial>>);
        static_assert(!bml::is_trivially_copy_assignable_v<bml::variant<triv_copy_assign, trivial,
            dtor_1>>);
    }
    
    // Check that the appropriate alternative's move constructor is called when a variant is move
    // constructed from another variant.
    {
        // Non-constexpr context.
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(bml::move(v1));
            
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::move(v1));
            
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::move(v1));
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double const volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double const volatile>(bml::move(v1));
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, move_ctor>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_ctor>(bml::move(v1));
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().move_ctor_called);
        }
        {
            auto v1 = bml::variant<int, move_ctor volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_ctor volatile>(bml::move(v1));
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().move_ctor_called);
        }
        {
            auto v1 = bml::variant<int, triv_move_ctor>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_move_ctor>(bml::move(v1));
            
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, triv_move_ctor, move_ctor>(bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, triv_move_ctor, move_ctor>(bml::move(v1));
            
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<2>().value == 42);
            bmltb_assert(v2.get<2>().move_ctor_called);
        }
        
        // Constexpr context (only available when move constructors are trivial; non-triviality
        // requires placement new to be emitted).
        {
            constexpr auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            constexpr auto v2 = bml::variant<int>(bml::move(v1));
            
            static_assert(v2.index() == 0);
            static_assert(v2.get<0>() == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            constexpr auto v2 = bml::variant<int, double>(bml::move(v1));
            
            static_assert(v2.index() == 0);
            static_assert(v2.get<0>() == 42);
        }
        {
            constexpr auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            constexpr auto v2 = bml::variant<int, double>(bml::move(v1));
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>() == 42.5);
        }
        {
            constexpr auto v1 = bml::variant<int, double const>(bml::in_place_index<1>, 42.5);
            constexpr auto v2 = bml::variant<int, double const>(bml::move(v1));
            
            static_assert(v2.index() == 1);
            static_assert(v2.get<1>() == 42.5);
        }
        {
            // Move constructors cannot bind to const, so testing for move construction when
            // alternatives are classes needs to be done through constexpr functions instead of
            // though declaring constexpr variants and moving them around.
            static_assert([]
            {
                auto v1 = bml::variant<int, triv_move_ctor>(bml::in_place_index<1>, 42);
                auto v2 = bml::variant<int, triv_move_ctor>(bml::move(v1));
                
                return v2.index() == 1 && v2.get<1>().value == 42;
            }());
            
            static_assert([]
            {
                auto v1 = bml::variant<int, trivial, triv_move_ctor>(bml::in_place_index<2>, 42);
                auto v2 = bml::variant<int, trivial, triv_move_ctor>(bml::move(v1));
                
                return v2.index() == 2 && v2.get<2>().value == 42;
            }());
        }
    }
    
    // Check that variant's move constructor does not participate in overload resolution if any
    // alternative is not move-constructible.
    {
        // "Move-constructible" since the variant is still copy-constructible - overload resolution
        // selects copy constructor.
        static_assert(bml::is_move_constructible_v<bml::variant<copy_ctor_no_move_ctor>>);
        static_assert(bml::is_move_constructible_v<bml::variant<copy_ctor_no_move_ctor, int>>);
        static_assert(bml::is_move_constructible_v<
            bml::variant<int volatile, copy_ctor_no_move_ctor, float const>>);
        
        // Not move-constructible since the variant is both not move-constructible and not
        // copy-constructible.
        static_assert(!bml::is_move_constructible_v<bml::variant<no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<implicit_no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<trivial const volatile>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<no_move_ctor const volatile>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<
            implicit_no_move_ctor const volatile>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<move_ctor, no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<move_ctor,
            implicit_no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<move_ctor volatile, double,
            no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::variant<move_ctor volatile,
            implicit_no_move_ctor const, int, double const>>);
    }
    
    // Check that variant's move constructor is trivial if all alternatives' move constructors are
    // trivial.
    {
        static_assert(bml::is_trivially_move_constructible_v<bml::variant<int>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::variant<int const>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::variant<int, trivial>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::variant<int, triv_move_ctor>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::variant<int, trivial,
            triv_move_ctor>>);
        
        static_assert(!bml::is_trivially_move_constructible_v<bml::variant<move_ctor>>);
        static_assert(!bml::is_trivially_move_constructible_v<bml::variant<move_ctor, int>>);
        static_assert(!bml::is_trivially_move_constructible_v<bml::variant<move_ctor volatile,
            int, trivial>>);
        static_assert(!bml::is_trivially_move_constructible_v<bml::variant<move_ctor const, int,
            trivial, triv_move_ctor>>);
    }
    
    // Check that the appropriate alternative's move assignment operator is called when a variant
    // is move assigned from another variant.
    {
        // Non-constexpr context, holding alternatives at same index.
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 10.8);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double volatile>(bml::in_place_index<1>, 10.8);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().move_assign_called);
        }
        {
            auto v1 = bml::variant<int, move_assign volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_assign volatile>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            bmltb_assert(v2.get<1>().move_assign_called);
        }
        {
            auto v1 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, move_assign volatile, triv_move_assign>(
                bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, move_assign volatile, triv_move_assign>(
                bml::in_place_index<2>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<2>().value == 42);
        }
        
        // Non-constexpr context, holding alternatives at different indices.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, double volatile>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double volatile>(bml::in_place_index<0>, 0);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>() == 42.5);
        }
        {
            auto v1 = bml::variant<int, move_assign>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, move_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            auto v1 = bml::variant<int, move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            
            // Should be emplaced via move construction, not move assigned.
            bmltb_assert(!v2.get<1>().move_assign_called);
        }
        {
            auto v1 = bml::variant<int, move_assign volatile>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, move_assign volatile>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
            
            // Should be emplaced via move construction, not move assigned.
            bmltb_assert(!v2.get<1>().move_assign_called);
        }
        {
            auto v1 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_move_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v2.get<1>().value == 42);
        }
        {
            auto v1 = bml::variant<int, move_assign volatile, triv_move_assign>(
                bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, move_assign volatile, triv_move_assign>(
                bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            bmltb_assert(&ref == &v2);
            bmltb_assert(v2.index() == 2);
            bmltb_assert(v2.get<1>().value == 42);
        }
        
        // Constexpr context, holding alternatives at same index (only available when alternatives'
        // move assignments, move constructors and destructors are trivial; non-triviality requires
        // placement new to be emitted).
        static_assert([]()
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 10.5);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>() == 42.5;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>().value == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, trivial, triv_move_assign>(bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, trivial, triv_move_assign>(bml::in_place_index<2>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 2 && v2.get<2>().value == 42;
        }());
        
        // Constexpr context, holding alternatives at different indices (only available when
        // alternatives' move assignments, move constructors and destructors are trivial;
        // non-triviality requires placement new to be emitted).
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 0 && v2.get<0>() == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<1>, 42.5);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>() == 42.5;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, triv_move_assign>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, triv_move_assign>(bml::in_place_index<0>, 10);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 1 && v2.get<1>().value == 42;
        }());
        
        static_assert([]()
        {
            auto v1 = bml::variant<int, trivial, triv_move_assign>(bml::in_place_index<2>, 42);
            auto v2 = bml::variant<int, trivial, triv_move_assign>(bml::in_place_index<1>);
            
            auto&& ref = (v2 = bml::move(v1));
            
            return (&ref == &v2) && v2.index() == 2 && v2.get<2>().value == 42;
        }());
    }
    
    // Check that variant's move assignment does not participate in overload resolution if any
    // alternative is not move-assignable or not move-constructible.
    {
        // "Move-assignable" since the variant is still copy-assignable - overload resolution
        // selects copy assignment operator.
        static_assert(bml::is_move_assignable_v<bml::variant<copyable_no_move_assign>>);
        static_assert(bml::is_move_assignable_v<bml::variant<copyable_no_move_assign, int>>);
        static_assert(bml::is_move_assignable_v<
            bml::variant<int volatile, copyable_no_move_assign, short>>);
        
        // Not move-assignable since the variant is both not move-assignable and not
        // move-constructible.
        static_assert(!bml::is_move_assignable_v<bml::variant<int const>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<double, int const>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<move_assign const volatile>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<implicit_no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<int, no_move_assign,
            implicit_no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<int, no_move_ctor>>);
        static_assert(!bml::is_move_assignable_v<bml::variant<int, move_assign, no_move_ctor>>);
    }
    
    // Check that variant's move assignment is trivial if all alternatives' move constructors, move
    // and assignments destructors are trivial.
    {
        static_assert(bml::is_trivially_move_assignable_v<bml::variant<int>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::variant<int volatile, double>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::variant<int volatile, trivial>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::variant<int, trivial,
            triv_move_assign>>);
        
        static_assert(!bml::is_trivially_move_assignable_v<bml::variant<move_assign>>);
        static_assert(!bml::is_trivially_move_assignable_v<bml::variant<move_assign volatile>>);
        static_assert(!bml::is_trivially_move_assignable_v<bml::variant<dtor_1>>);
        static_assert(!bml::is_trivially_move_assignable_v<bml::variant<int const, trivial>>);
        static_assert(!bml::is_trivially_move_assignable_v<bml::variant<triv_move_assign, trivial,
            dtor_1>>);
    }
    
    // Check that the destructor of the current alternative is only invoked when the variant is
    // destroyed or takes on an alternative at a different index.
    {
        // Check that destructor is called after going out of scope.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v = bml::variant<dtor_1>(bml::in_place_index<0>);
        }
        bmltb_assert(dtor_1::count == 1);
        bmltb_assert(dtor_2::count == 0);
        
        // Check that correct alternative's destructor is called after going out of scope.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2, int>(bml::in_place_index<1>);
            auto v2 = bml::variant<dtor_1, dtor_2, int>(bml::in_place_index<2>);
        }
        bmltb_assert(dtor_1::count == 0);
        bmltb_assert(dtor_2::count == 1);
        
        // Check that destructor is not called during copy construction.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2, int>(bml::in_place_index<0>);
            {
                auto v2 = bml::variant<dtor_1, dtor_2, int>(v1);
                bmltb_assert(dtor_1::count == 0);
                bmltb_assert(dtor_2::count == 0);
            }
            bmltb_assert(dtor_1::count == 1);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 0);
        
        // Check that destructor is not called during move construction.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2, int>(bml::in_place_index<0>);
            {
                auto v2 = bml::variant<dtor_1, dtor_2, int>(bml::move(v1));
                bmltb_assert(dtor_1::count == 0);
                bmltb_assert(dtor_2::count == 0);
            }
            bmltb_assert(dtor_1::count == 1);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 0);
        
        // Check that assignee's destructor is called on copy assignment when the assignee holds an
        // alternative at a different index from the assigner.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            auto v2 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<1>);
            
            v2 = v1;
            
            bmltb_assert(dtor_1::count == 0);
            bmltb_assert(dtor_2::count == 1);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 1);
        
        // Check that assignee's destructor is not called on copy assignment when the assignee holds
        // an alternative at the same index as the assigner.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            auto v2 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            
            v2 = v1;
            
            bmltb_assert(dtor_1::count == 0);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 0);
        
        // Check that assignee's destructor is called on move assignment when the assignee holds an
        // alternative at a different index from the assigner.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            auto v2 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<1>);
            
            v2 = bml::move(v1);
            bmltb_assert(dtor_1::count == 0);
            bmltb_assert(dtor_2::count == 1);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 1);
        
        // Check that assignee's destructor is not called on move assignment when the assignee holds
        // an alternative at the same index as the assigner.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v1 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            auto v2 = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            
            v2 = bml::move(v1);
            
            bmltb_assert(dtor_1::count == 0);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 0);
        
        // Check that the destructor is called when an alternative at a different index is emplaced
        // into the variant.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            v.emplace<1>();
            
            bmltb_assert(dtor_1::count == 1);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 1);
        bmltb_assert(dtor_2::count == 1);
        
        // Check that the destructor is called when an alternative at the same index is emplaced
        // into the variant.
        dtor_1::count = 0; dtor_2::count = 0;
        {
            auto v = bml::variant<dtor_1, dtor_2>(bml::in_place_index<0>);
            v.emplace<0>();
            
            bmltb_assert(dtor_1::count == 1);
            bmltb_assert(dtor_2::count == 0);
        }
        bmltb_assert(dtor_1::count == 2);
        bmltb_assert(dtor_2::count == 0);
    }
    
    // Check that variant is not destructible if any alternative is not destructible.
    {
        static_assert(!bml::is_destructible_v<bml::variant<no_dtor>>);
        static_assert(!bml::is_destructible_v<bml::variant<no_dtor const volatile>>);
        static_assert(!bml::is_destructible_v<bml::variant<dtor_1, no_dtor const volatile>>);
        static_assert(!bml::is_destructible_v<bml::variant<trivial, int, no_dtor>>);
    }
    
    // Check that variant's destructor is trivial if all alternatives' destructors are trivial.
    {
        static_assert(bml::is_trivially_destructible_v<bml::variant<int>>);
        static_assert(bml::is_trivially_destructible_v<bml::variant<int const>>);
        static_assert(bml::is_trivially_destructible_v<bml::variant<int, trivial>>);
        static_assert(bml::is_trivially_destructible_v<bml::variant<int, trivial const>>);
        static_assert(bml::is_trivially_destructible_v<bml::variant<int, trivial, trivial const>>);
        
        static_assert(!bml::is_trivially_destructible_v<bml::variant<dtor_1>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<int, dtor_1>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<dtor_1, dtor_2>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<int, dtor_1 const>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<int, dtor_1, trivial>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<no_dtor>>);
        static_assert(!bml::is_trivially_destructible_v<bml::variant<int, no_dtor>>);
    }
    
    // Check that variant_alternative names the I-th alternative in the variant, with the variant's
    // cv-qualifiers applied to that alternative.
    {
        check_variant_alternative<0, bml::variant<int>, int>();
        
        check_variant_alternative<0, bml::variant<int, double const volatile>,
            int>();
        check_variant_alternative<1, bml::variant<int, double const volatile>,
            double const volatile>();
        
        check_variant_alternative<0, bml::variant<int const**, double, ctor const>, int const**>();
        check_variant_alternative<1, bml::variant<int const**, double, ctor const>, double>();
        check_variant_alternative<2, bml::variant<int const**, double, ctor const>, ctor const>();
    }
    
    // Check that variant_size yields the number of alternatives in the variant.
    {
        check_variant_size<bml::variant<int>, 1>();
        check_variant_size<bml::variant<int, double const>, 2>();
        check_variant_size<bml::variant<int const volatile, double const, no_dtor>, 3>();
    }
    
    // Check that member get returns a reference to the I-th alternative that is of the appropriate
    // type for the variant's value category (i.e. lvalue reference if the variant is an lvalue,
    // rvalue reference otherwise), with the variant's const qualification applied to that
    // alternative.
    {
        // Check return type.
        check_member_get_type<bml::variant<int>, 0, int>();
        check_member_get_type<bml::variant<int, double const>, 1, double const>();
        check_member_get_type<bml::variant<int, copy_ctor volatile>, 1, copy_ctor volatile>();
        check_member_get_type<bml::variant<int, copy_ctor, double const*>, 2, double const*>();
        check_member_get_type<bml::variant<int**, copy_ctor, double const*>, 0, int**>();
        
        // Check that correct reference is returned.
        static_assert([]
        {
            auto v = bml::variant<bool>(bml::in_place_index<0>, true);
            return v.get<0>();
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<0>, 42);
            return v.get<0>() == 42;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<0>, 42);
            v.get<0>() = 500;
            
            return v.get<0>() == 500;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<1>, 42);
            return v.get<1>().value == 42;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<1>, 42);
            v.get<1>().value = 500;
            
            return v.get<1>().value == 500;
        }());
    }
    
    // Check that non-member get returns a reference to the I-th alternative that is of the
    // appropriate type for the variant's value category (i.e. lvalue reference if the variant is an
    // lvalue, rvalue reference otherwise), with the variant's const qualification applied to that
    // alternative.
    {
        // Check return type.
        check_free_get_type<bml::variant<int>, 0, int>();
        check_free_get_type<bml::variant<int, double const>, 1, double const>();
        check_free_get_type<bml::variant<int, copy_ctor volatile>, 1, copy_ctor volatile>();
        check_free_get_type<bml::variant<int, copy_ctor, double const*>, 2, double const*>();
        check_free_get_type<bml::variant<int**, copy_ctor, double const*>, 0, int**>();
        
        // Check that correct reference is returned.
        static_assert([]
        {
            auto v = bml::variant<bool>(bml::in_place_index<0>, true);
            return bml::get<0>(v);
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<0>, 42);
            return bml::get<0>(v) == 42;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<0>, 42);
            bml::get<0>(v) = 500;
            
            return bml::get<0>(v) == 500;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<1>, 42);
            return bml::get<1>(v).value == 42;
        }());
        
        static_assert([]
        {
            auto v = bml::variant<int, ctor>(bml::in_place_index<1>, 42);
            bml::get<1>(v).value = 500;
            
            return bml::get<1>(v).value == 500;
        }());
    }
    
    // Check that visit forwards the value category of the visitor and its variants to the
    // visitor's function call operator.
    {
        auto vis = visit_sniffer();
        auto const& cvis = vis;
        
        // No variants.
        {
            bmltb_assert(bml::visit(vis) ==
                visit_sniffer::result<visit_sniffer::lvalue>::id());
            bmltb_assert(bml::visit(cvis) ==
                visit_sniffer::result<visit_sniffer::const_lvalue>::id());
            bmltb_assert(bml::visit(bml::move(vis)) ==
                visit_sniffer::result<visit_sniffer::rvalue>::id());
            bmltb_assert(bml::visit(bml::move(cvis)) ==
                visit_sniffer::result<visit_sniffer::const_rvalue>::id());
        }
        
        // Single variant.
        {
            auto v = bml::variant<int>(bml::in_place_index<0>, 42);
            auto const& cv = v;
            
            bmltb_assert(bml::visit(vis, v) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&>::id());
            bmltb_assert(bml::visit(cvis, v) ==
                visit_sniffer::result<visit_sniffer::const_lvalue, int&>::id());
            bmltb_assert(bml::visit(bml::move(vis), v) ==
                visit_sniffer::result<visit_sniffer::rvalue, int&>::id());
            bmltb_assert(bml::visit(bml::move(cvis), v) ==
                visit_sniffer::result<visit_sniffer::const_rvalue, int&>::id());
            
            bmltb_assert(bml::visit(vis, cv) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&>::id());
            bmltb_assert(bml::visit(cvis, cv) ==
                visit_sniffer::result<visit_sniffer::const_lvalue, int const&>::id());
            bmltb_assert(bml::visit(bml::move(vis), cv) ==
                visit_sniffer::result<visit_sniffer::rvalue, int const&>::id());
            bmltb_assert(bml::visit(bml::move(cvis), cv) ==
                visit_sniffer::result<visit_sniffer::const_rvalue, int const&>::id());
            
            bmltb_assert(bml::visit(vis, bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&&>::id());
            bmltb_assert(bml::visit(cvis, bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::const_lvalue, int&&>::id());
            bmltb_assert(bml::visit(bml::move(vis), bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::rvalue, int&&>::id());
            bmltb_assert(bml::visit(bml::move(cvis), bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::const_rvalue, int&&>::id());
            
            bmltb_assert(bml::visit(vis, bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&&>::id());
            bmltb_assert(bml::visit(cvis, bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::const_lvalue, int const&&>::id());
            bmltb_assert(bml::visit(bml::move(vis), bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::rvalue, int const&&>::id());
            bmltb_assert(bml::visit(bml::move(cvis), bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::const_rvalue, int const&&>::id());
        }
        
        // Multiple variants.
        {
            auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<double>(bml::in_place_index<0>, 42.5);
            auto const& cv1 = v1;
            auto const& cv2 = v2;
            
            bmltb_assert(bml::visit(vis, v1, v2) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&, double&>::id());
            bmltb_assert(bml::visit(vis, v2, v1) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&, int&>::id());
            bmltb_assert(bml::visit(vis, v1, v1) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&, int&>::id());
            bmltb_assert(bml::visit(vis, v2, v2) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&, double&>::id());
            
            bmltb_assert(bml::visit(vis, cv1, cv2) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&, double const&>::id());
            bmltb_assert(bml::visit(vis, cv2, cv1) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&, int const&>::id());
            bmltb_assert(bml::visit(vis, cv1, cv1) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&, int const&>::id());
            bmltb_assert(bml::visit(vis, cv2, cv2) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&, double const&>::id());
            
            bmltb_assert(bml::visit(vis, bml::move(v1), bml::move(v2)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&&, double&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v2), bml::move(v1)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&&, int&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v1), bml::move(v1)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&&, int&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v2), bml::move(v2)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&&, double&&>::id());
            
            bmltb_assert(bml::visit(vis, bml::move(cv1), bml::move(cv2)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&&, double const&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv2), bml::move(cv1)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&&, int const&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv1), bml::move(cv1)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&&, int const&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv2), bml::move(cv2)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&&, double const&&>::id());
            
            auto v3 = bml::variant<char>(bml::in_place_index<0>, 'a');
            auto const& cv3 = v3;
            
            bmltb_assert(bml::visit(vis, bml::move(cv1), v2, cv3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    int const&&, double&, char const&>::id());
            bmltb_assert(bml::visit(cvis, cv2, bml::move(v3), bml::move(cv1)) ==
                visit_sniffer::result<visit_sniffer::const_lvalue,
                    double const&, char&&, int const&&>::id());
            bmltb_assert(bml::visit(bml::move(cvis), cv2, v3, bml::move(cv2)) ==
                visit_sniffer::result<visit_sniffer::const_rvalue,
                    double const&, char&, double const&&>::id());
            bmltb_assert(bml::visit(bml::move(vis), cv1, v3, cv2, bml::move(v3), bml::move(v1)) ==
                visit_sniffer::result<visit_sniffer::rvalue,
                    int const&, char&, double const&, char&&, int&&>::id());
        }
    }
    
    // Check that visit visits variants at the their current index.
    {
        auto vis = visit_sniffer();
        
        // Single variant.
        {
            auto val_checker = overload{
                [](int const& i)    noexcept { return i == 42;    },
                [](char const& c)   noexcept { return c == 'a';   },
                [](double const& d) noexcept { return d == 101.5; }
            };
            
            // int case.
            auto v = bml::variant<int, char, double>(bml::in_place_index<0>, 42);
            auto const& cv = v;
            
            bmltb_assert(bml::visit(vis, v) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&>::id());
            bmltb_assert(bml::visit(vis, cv) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::lvalue, int const&&>::id());
            
            bmltb_assert(bml::visit(val_checker, v));    
            bmltb_assert(bml::visit(val_checker, cv));
            
            // char case.
            v.emplace<1>('a');
            
            bmltb_assert(bml::visit(vis, v) ==
                visit_sniffer::result<visit_sniffer::lvalue, char&>::id());
            bmltb_assert(bml::visit(vis, cv) ==
                visit_sniffer::result<visit_sniffer::lvalue, char const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::lvalue, char&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::lvalue, char const&&>::id());
            
            bmltb_assert(bml::visit(val_checker, v));    
            bmltb_assert(bml::visit(val_checker, cv));
            
            // double case.
            v.emplace<2>(101.5);
            
            bmltb_assert(bml::visit(vis, v) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&>::id());
            bmltb_assert(bml::visit(vis, cv) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv)) ==
                visit_sniffer::result<visit_sniffer::lvalue, double const&&>::id());
            
            bmltb_assert(bml::visit(val_checker, v));    
            bmltb_assert(bml::visit(val_checker, cv));
        }
        
        // Multiple variants with default case.
        {
            auto val_checker = overload{
                [](int const& i, short const& s, float const& f) noexcept
                {
                    return i == 42 && s == 4 && f == 4200.5;
                },
                [](char const& c, long const& l, ctor const& ct) noexcept
                {
                    return c == 'a' && l == 420 && ct.value == 10;
                },
                [](double const& d, short const& s, ctor const& ct) noexcept
                {
                    return d == 100.5 && s == 12 && ct.value == 22;
                },
                [](auto, auto, auto) noexcept
                {
                    return false;
                }
            };
            
            // int, short, float case.
            auto v1 = bml::variant<int, char, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<short, long>(bml::in_place_index<0>, 4);
            auto v3 = bml::variant<float, ctor>(bml::in_place_index<0>, 4200.5);
            
            auto const& cv1 = v1;
            auto const& cv2 = v2;
            auto const& cv3 = v3;
            
            bmltb_assert(bml::visit(vis, v1, v2, v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    int&, short&, float&>::id());
            bmltb_assert(bml::visit(vis, cv1, cv2, cv3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    int const&, short const&, float const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v1), v2, bml::move(v3)) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    int&&, short&, float&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv1), bml::move(cv2), v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    int const&&, short const&&, float&>::id());
            
            bmltb_assert(bml::visit(val_checker, v1, v2, v3));
            bmltb_assert(bml::visit(val_checker, cv1, cv2, cv3));
            bmltb_assert(bml::visit(val_checker, cv1, v2, cv3));
            
            // char, long, ctor case.
            v1.emplace<1>('a');
            v2.emplace<1>(420);
            v3.emplace<1>(10);
            
            bmltb_assert(bml::visit(vis, v1, v2, v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    char&, long&, ctor&>::id());
            bmltb_assert(bml::visit(vis, cv1, cv2, cv3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    char const&, long const&, ctor const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v1), v2, bml::move(v3)) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    char&&, long&, ctor&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv1), bml::move(cv2), v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    char const&&, long const&&, ctor&>::id());
                    
            bmltb_assert(bml::visit(val_checker, v1, v2, v3));
            bmltb_assert(bml::visit(val_checker, cv1, cv2, cv3));
            bmltb_assert(bml::visit(val_checker, cv1, v2, cv3));
            
            // double, short, ctor case (with different values).
            v1.emplace<2>(100.5);
            v2.emplace<0>(12);
            v3.emplace<1>(22);
            
            bmltb_assert(bml::visit(vis, v1, v2, v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    double&, short&, ctor&>::id());
            bmltb_assert(bml::visit(vis, cv1, cv2, cv3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    double const&, short const&, ctor const&>::id());
            bmltb_assert(bml::visit(vis, bml::move(v1), v2, bml::move(v3)) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    double&&, short&, ctor&&>::id());
            bmltb_assert(bml::visit(vis, bml::move(cv1), bml::move(cv2), v3) ==
                visit_sniffer::result<visit_sniffer::lvalue,
                    double const&&, short const&&, ctor&>::id());
                    
            bmltb_assert(bml::visit(val_checker, v1, v2, v3));
            bmltb_assert(bml::visit(val_checker, cv1, cv2, cv3));
            bmltb_assert(bml::visit(val_checker, cv1, v2, cv3));
            
            // Default case.
            v1.emplace<0>(42);
            v2.emplace<0>(4);
            v3.emplace<1>(42);
            
            bmltb_assert(!bml::visit(val_checker, v1, v2, v3));
            bmltb_assert(!bml::visit(val_checker, cv1, cv2, cv3));
            bmltb_assert(!bml::visit(val_checker, cv1, v2, cv3));
        }
    }
    
    // Check that visit is usable in a constexpr context.
    {
        constexpr auto return_first = [](auto& a, auto&&...) { return a; };
        constexpr auto return_sizeof = [](auto&&... as) { return sizeof...(as); };
        
        constexpr auto v1 = bml::variant<int>(bml::in_place_index<0>, 42);
        static_assert(bml::visit(return_first, v1) == 42);
        static_assert(bml::visit(return_sizeof, v1) == 1);
        
        constexpr auto v2 = bml::variant<int, double, float>(bml::in_place_index<1>, 100.5);
        static_assert(bml::visit(return_first, v1, v2) == 42);
        static_assert(bml::visit(return_sizeof, v1, v2) == 2);
        
        constexpr auto v3 = bml::variant<ctor, short, unsigned int>(bml::in_place_index<0>, 9000);
        static_assert(bml::visit(return_first, v1, v2, v3, bml::move(v2)) == 42);
        static_assert(bml::visit(return_sizeof, v1, v2, v3, bml::move(v2)) == 4);
    }
    
    // Check that visit does not participate in overload resolution if its arguments (other than the
    // visitor) are not all variants.
    {
        constexpr auto vis = [](int, int) { return 42; };
        constexpr auto v1 = bml::variant<int>(bml::in_place_index<0>, 2);
        
        using bml::visit;
        using ::visit;
        static_assert(visit(vis, v1, 9000) == 100);
    }
    
    // Check that emplace constructs a new value in-place.
    {
        // Emplace with different index.
        {
            auto v = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto& r = v.emplace<1>(100.5);
            
            static_assert(bml::is_same_v<decltype(r), double&>);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 100.5);
            bmltb_assert(&v.get<1>() == &r);
        }
        {
            auto v = bml::variant<int volatile, double>(bml::in_place_index<1>, 100.5);
            auto& r = v.emplace<0>();
            
            static_assert(bml::is_same_v<decltype(r), int volatile&>);
            bmltb_assert(v.index() == 0);
            bmltb_assert(v.get<0>() == 0);
            bmltb_assert(&v.get<0>() == &r);
        }
        {
            auto v = bml::variant<int, double, char>(bml::in_place_index<0>, 42);
            v.emplace<1>(100.5);
            auto& r = v.emplace<2>('a');
            
            static_assert(bml::is_same_v<decltype(r), char&>);
            bmltb_assert(v.index() == 2); 
            bmltb_assert(v.get<2>() == 'a');
            bmltb_assert(&v.get<2>() == &r);
        }
        {
            auto v = bml::variant<int, double const, char>(bml::in_place_index<0>, 42);
            v.emplace<2>('a');
            auto& r = v.emplace<1>(100.5);
            
            static_assert(bml::is_same_v<decltype(r), double const&>);
            bmltb_assert(v.index() == 1); 
            bmltb_assert(v.get<1>() == 100.5);
            bmltb_assert(&v.get<1>() == &r);
        }
        {
            auto v = bml::variant<int, ctor, multiply const>(bml::in_place_index<0>, 42);
            v.emplace<1>(42);
            auto& r = v.emplace<2>(5, 10);
            
            static_assert(bml::is_same_v<decltype(r), multiply const&>);
            bmltb_assert(v.index() == 2); 
            bmltb_assert(v.get<2>().value == 50);
            bmltb_assert(&v.get<2>() == &r);
        }
        
        // Emplace with same index.
        {
            auto v = bml::variant<int>(bml::in_place_index<0>, 42);
            auto& r = v.emplace<0>(10);
            
            static_assert(bml::is_same_v<decltype(r), int&>);
            bmltb_assert(v.index() == 0); 
            bmltb_assert(v.get<0>() == 10);
            bmltb_assert(&v.get<0>() == &r);
        }
        {
            auto v = bml::variant<int, double volatile>(bml::in_place_index<1>, 100.5);
            auto& r = v.emplace<1>();
            
            static_assert(bml::is_same_v<decltype(r), double volatile&>);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 0);
            bmltb_assert(&v.get<1>() == &r);
        }
        {
            auto v = bml::variant<int const, double>(bml::in_place_index<1>, 100.5);
            v.emplace<1>();
            auto& r = v.emplace<1>(42.42);
            
            static_assert(bml::is_same_v<decltype(r), double&>);
            bmltb_assert(v.index() == 1);
            bmltb_assert(v.get<1>() == 42.42);
            bmltb_assert(&v.get<1>() == &r);
        }
        {
            auto v = bml::variant<int, ctor, multiply const>(bml::in_place_index<2>, 5, 10);
            v.emplace<2>(6, 11);
            auto& r = v.emplace<2>(7, 12);
            
            static_assert(bml::is_same_v<decltype(r), multiply const&>);
            bmltb_assert(v.index() == 2); 
            bmltb_assert(v.get<2>().value == 84);
            bmltb_assert(&v.get<2>() == &r);
        }
    }
    
    // Check that emplace is not callable if the alternative at index I is not constructible from
    // emplace's arguments.
    {
        static_assert(!can_call_emplace<bml::variant<void*>, 0, int const*>());
        static_assert(!can_call_emplace<bml::variant<int>, 0, int, int>());
        static_assert(!can_call_emplace<bml::variant<ctor const volatile>, 0, bmltb::union_type>());
        static_assert(!can_call_emplace<bml::variant<multiply>, 0>());
        static_assert(!can_call_emplace<bml::variant<multiply>, 0, int>());
        static_assert(!can_call_emplace<bml::variant<multiply>, 0, ctor>());
        
        static_assert(!can_call_emplace<bml::variant<double, int const>, 1, int, int>());
        static_assert(!can_call_emplace<bml::variant<int, ctor>, 1>());
        static_assert(!can_call_emplace<bml::variant<int, ctor volatile>, 1, bmltb::class_type>());
        
        static_assert(!can_call_emplace<bml::variant<multiply, ctor, int>, 2, int, int>());
        static_assert(!can_call_emplace<bml::variant<multiply, ctor, int>, 1, int, int>());
        static_assert(!can_call_emplace<bml::variant<multiply, ctor, int>, 0, int>());
    }
    
    // Check that member swap swaps the variant's currently held value with the argument variant's
    // value.
    {
        // Holding alternatives at same index.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 24);
            
            v1.swap(v2);
            
            bmltb_assert(v1.index() == 0);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v1.get<0>() == 24);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            // Check that this calls the user-defined swap if it's available.
            
            swappee::swap_called = false;
            auto v1 = bml::variant<int, swappee>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, swappee>(bml::in_place_index<1>, 24);
            
            v1.swap(v2);
            
            bmltb_assert(swappee::swap_called);
            
            bmltb_assert(v1.index() == 1);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v1.get<1>().value == 24);
            bmltb_assert(v2.get<1>().value == 42);
        }
        
        // Holding alternatives at different indices.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 100.5);
            
            v1.swap(v2);
            
            bmltb_assert(v1.index() == 1);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v1.get<1>() == 100.5);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            swappee::swap_called = false;
            auto v1 = bml::variant<int, swappee>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, swappee>(bml::in_place_index<0>, 24);
            
            v1.swap(v2);
            
            // Should be move constructed.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(v1.index() == 0);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v1.get<0>() == 24);
            bmltb_assert(v2.get<1>().value == 42);
        }
    }
    
    // Check that member swap is not callable if any alternative is not swappable or not
    // move-constructible.
    {
        static_assert(!can_call_mem_swap<bml::variant<no_move_ctor>>());
        static_assert(!can_call_mem_swap<bml::variant<not_swappable>>());
        static_assert(!can_call_mem_swap<bml::variant<int, no_move_ctor, double>>());
        static_assert(!can_call_mem_swap<bml::variant<int, not_swappable, double>>());
    }
    
    // Check that free swap swaps two variant's currently held values.
    {
        // Holding alternatives at the same index.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<0>, 24);
            
            using bml::swap;
            using ::swap;
            swap(v1, v2);
            
            bmltb_assert(v1.index() == 0);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v1.get<0>() == 24);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            // Check that this calls the user-defined swap if it's available.
            
            swappee::swap_called = false;
            auto v1 = bml::variant<int, swappee>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, swappee>(bml::in_place_index<1>, 24);
            
            using bml::swap;
            using ::swap;
            swap(v1, v2);
            
            bmltb_assert(swappee::swap_called);
            
            bmltb_assert(v1.index() == 1);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v1.get<1>().value == 24);
            bmltb_assert(v2.get<1>().value == 42);
        }
        
        // Holding alternatives at different indices.
        {
            auto v1 = bml::variant<int, double>(bml::in_place_index<0>, 42);
            auto v2 = bml::variant<int, double>(bml::in_place_index<1>, 100.5);
            
            using bml::swap;
            using ::swap;
            swap(v1, v2);
            
            bmltb_assert(v1.index() == 1);
            bmltb_assert(v2.index() == 0);
            bmltb_assert(v1.get<1>() == 100.5);
            bmltb_assert(v2.get<0>() == 42);
        }
        {
            swappee::swap_called = false;
            auto v1 = bml::variant<int, swappee>(bml::in_place_index<1>, 42);
            auto v2 = bml::variant<int, swappee>(bml::in_place_index<0>, 24);
            
            using bml::swap;
            using ::swap;
            swap(v1, v2);
            
            // Should be move constructed.
            bmltb_assert(!swappee::swap_called);
            
            bmltb_assert(v1.index() == 0);
            bmltb_assert(v2.index() == 1);
            bmltb_assert(v1.get<0>() == 24);
            bmltb_assert(v2.get<1>().value == 42);
        }
    }
    
    // Check that free swap is not callable if any alternative is not swappable or not
    // move-constructible, and the variant itself is not move-constructible or move-assignable (so
    // that the "generic" swap cannot be used).
    {
        static_assert(!bml::is_swappable_v<bml::variant<no_move_ctor>>);
        static_assert(!bml::is_swappable_v<bml::variant<not_swappable, no_move_assign>>);
        static_assert(!bml::is_swappable_v<bml::variant<int, not_swappable, no_move_assign>>);
        static_assert(!bml::is_swappable_v<bml::variant<int, no_move_ctor, double>>);
    }
    
    return 0;
}
