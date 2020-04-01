//
// Copyright (c) 2020 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#include <bml_testbench.hpp>
#include <bml/containers/array.hpp>
#include <bml/basic_types/nullptr_ty.hpp>
#include <bml/type_traits/is_aggregate.hpp>
#include <bml/type_traits/is_constructible.hpp>
#include <bml/type_traits/is_default_constructible.hpp>
#include <bml/type_traits/is_trivially_default_constructible.hpp>
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
#include <bml/type_traits/is_detected.hpp>
#include <bml/type_traits/is_swappable.hpp>
#include <bml/type_traits/is_same.hpp>
#include <bml/utilities/move.hpp>
#include <bml/utilities/declval.hpp>

struct default_ctor
{
    int i;

    constexpr default_ctor() : i(42) {}
};

struct no_default_ctor
{
    int i;

    no_default_ctor() = delete;
    constexpr no_default_ctor(int x) : i(x) {}
};

struct copy_ctor
{
    int value;
    bool copy_ctor_called;

    constexpr copy_ctor(int i) : value(i), copy_ctor_called(false) {}
    constexpr copy_ctor(copy_ctor const& other) : value(other.value), copy_ctor_called(true) {}
    copy_ctor(copy_ctor const volatile& other) : value(other.value), copy_ctor_called(true) {}

    auto operator=(copy_ctor const&)->copy_ctor & = delete;
    copy_ctor(copy_ctor&&) = delete;
    auto operator=(copy_ctor&&)->copy_ctor & = delete;
};

struct triv_copy_ctor
{
    int value;

    constexpr triv_copy_ctor(int i) : value(i) {}
    triv_copy_ctor(triv_copy_ctor const&) = default;

    auto operator=(triv_copy_ctor const&)->triv_copy_ctor & = delete;
    triv_copy_ctor(triv_copy_ctor&&) = delete;
    auto operator=(triv_copy_ctor&&)->triv_copy_ctor & = delete;
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

    constexpr auto operator=(copy_assign const& other) -> copy_assign&
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

    copy_assign(copy_assign const&) = delete;
    copy_assign(copy_assign&&) = delete;
    auto operator=(copy_assign&&)->copy_assign & = delete;
};

struct triv_copy_assign
{
    int value;

    constexpr triv_copy_assign(int i) : value(i) {}

    auto operator=(triv_copy_assign const&)->triv_copy_assign & = default;

    triv_copy_assign(triv_copy_assign const&) = delete;
    triv_copy_assign(triv_copy_assign&&) = delete;
    auto operator=(triv_copy_assign&&)->triv_copy_assign & = delete;
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

    auto operator=(move_ctor&&)->move_ctor & = delete;
    move_ctor(move_ctor const&) = delete;
    auto operator=(move_ctor const&)->move_ctor & = delete;
};

struct triv_move_ctor
{
    int value;

    constexpr triv_move_ctor(int i) : value(i) {}
    triv_move_ctor(triv_move_ctor&&) = default;

    auto operator=(triv_move_ctor&&)->triv_move_ctor & = delete;
    triv_move_ctor(triv_move_ctor const&) = delete;
    auto operator=(triv_move_ctor const&)->triv_move_ctor & = delete;
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

    constexpr auto operator=(move_assign&& other) -> move_assign&
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
    move_assign(move_assign&&) = delete;
    auto operator=(move_assign const&)->move_assign & = delete;
};

struct triv_move_assign
{
    int value;

    constexpr triv_move_assign(int i) : value(i) {}

    auto operator=(triv_move_assign&&)->triv_move_assign & = default;

    triv_move_assign(triv_move_assign const&) = delete;
    auto operator=(triv_move_assign const&)->triv_move_assign & = delete;
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
    auto operator=(copyable_no_move_assign const&)->copyable_no_move_assign & = default;

    auto operator=(copyable_no_move_assign&&) = delete;
};

struct dtor
{
    inline static auto count = 0;

    dtor() = default;
    ~dtor() { ++count; }

    dtor(dtor const&) = default;
    dtor(dtor&&) = default;
    auto operator=(dtor const&)->dtor & = default;
    auto operator=(dtor&&)->dtor & = default;
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

template <typename T>
using has_subscript_op = decltype(bml::declval<T&>()[bml::declval<int>()]);

template <typename T>
using has_mem_get = decltype(bml::declval<T&>().template get<0>());

template <typename T>
using has_front = decltype(bml::declval<T&>().front());

template <typename T>
using has_back = decltype(bml::declval<T&>().back());

template <typename T>
using has_data = decltype(bml::declval<T&>().data());

template <typename T>
using has_fill_int = decltype(bml::declval<T&>().fill(bml::declval<int const&>()));

template <typename T>
using has_fill_default_ctor = decltype(
    bml::declval<T&>().fill(bml::declval<default_ctor const&>()));

template <typename T>
using has_mem_swap = decltype(bml::declval<T&>().template swap(bml::declval<T&>()));

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
auto swap(not_swappable&, not_swappable&) = delete;

struct not_swappable_or_movable
{
    not_swappable_or_movable(not_swappable_or_movable&&) = delete;
    auto operator=(not_swappable_or_movable&&) = delete;

};
auto swap(not_swappable_or_movable&, not_swappable_or_movable&) = delete;

auto test_main() noexcept -> int
{
    // Check that array is default-constructible when its type is default-constructible or if it is
    // of zero length.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 10>();
            bmltb_assert(a.size() == 10);
        }
        {
            auto a = bml::array<float volatile, 10>();
            bmltb_assert(a.size() == 10);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>();
            static_assert(a.size() == 3);
        }
        {
            constexpr auto a = bml::array<char, 5>();
            static_assert(a.size() == 5);
        }
        {
            constexpr auto a = bml::array<bml::nullptr_ty, 42>();
            static_assert(a.size() == 42);
        }
        {
            constexpr auto a = bml::array<default_ctor, 2>();
            static_assert(a.size() == 2);
            static_assert(a[0].i == 42);
            static_assert(a[1].i == 42);
        }

        // Zero length.
        {
            constexpr auto a = bml::array<default_ctor, 0>();
            static_assert(a.size() == 0);
        }
        {
            constexpr auto a = bml::array<no_default_ctor, 0>();
            static_assert(a.size() == 0);
        }
    }

    // Check that array cannot be default constructed when it is of non-zero length and either its
    // type is not default-constructible or its type is const qualified (const qualification causes
    // array's default constructor to be deleted).
    {
        static_assert(!bml::is_default_constructible_v<bml::array<no_default_ctor, 3>>);
        static_assert(!bml::is_default_constructible_v<bml::array<int const, 3>>);
        static_assert(!bml::is_default_constructible_v<bml::array<int const volatile, 3>>);
    }

    // Check that array is trivially default-constructible if its type is trivially
    // default-constructible and not const-qualified, or if it is of zero length.
    {
        static_assert(bml::is_trivially_default_constructible_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_default_constructible_v<bml::array<int volatile, 42>>);
        static_assert(bml::is_trivially_default_constructible_v<bml::array<no_default_ctor, 0>>);
    }

    // Check that array is an aggregate type and that it can be initialized via aggregate
    // initialization.
    {
        {
            static_assert(bml::is_aggregate_v<bml::array<int, 3>>);
            static_assert(bml::is_aggregate_v<bml::array<char volatile, 3>>);
            static_assert(bml::is_aggregate_v<bml::array<float const, 3>>);
            static_assert(bml::is_aggregate_v<bml::array<default_ctor, 3>>);
            static_assert(bml::is_aggregate_v<bml::array<no_default_ctor, 3>>);
        }

        // Non-constexpr context.
        {
            auto a = bml::array<char, 3>{'a', 'b', 'c'};
            bmltb_assert(a[0] == 'a');
            bmltb_assert(a[1] == 'b');
            bmltb_assert(a[2] == 'c');
        }
        {
            auto a = bml::array<int volatile, 3>{20, 8, -12};
            bmltb_assert(a[0] == 20);
            bmltb_assert(a[1] == 8);
            bmltb_assert(a[2] == -12);
        }

        // Contexpr context.
        {
            constexpr auto a = bml::array<char, 3>{'a', 'b', 'c'};
            static_assert(a[0] == 'a');
            static_assert(a[1] == 'b');
            static_assert(a[2] == 'c');
        }
        {
            constexpr auto a = bml::array<int const, 3>{20, 8, -12};
            static_assert(a[0] == 20);
            static_assert(a[1] == 8);
            static_assert(a[2] == -12);
        }
        {
            constexpr auto a = bml::array<no_default_ctor, 3>{20, 8, -12};
            static_assert(a[0].i == 20);
            static_assert(a[1].i == 8);
            static_assert(a[2].i == -12);
        }
        {
            constexpr auto a = bml::array<no_default_ctor, 0>{};
            static_assert(a.size() == 0);
        }
    }

    // Check that array is copy-constructible when its type is copy-constructible or if it is of
    // zero length.
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>(a1);
            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
        }
        {
            auto a1 = bml::array<int volatile, 2>{42, 24};
            auto a2 = bml::array<int volatile, 2>(a1);
            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
        }

        // Constexpr context.
        {
            constexpr auto a1 = bml::array<int, 2>{42, 24};
            constexpr auto a2 = bml::array<int, 2>(a1);
            static_assert(a2[0] == 42);
            static_assert(a2[1] == 24);
        }
        {
            constexpr auto a1 = bml::array<int const, 2>{42, 24};
            constexpr auto a2 = bml::array<int const, 2>(a1);
            static_assert(a2[0] == 42);
            static_assert(a2[1] == 24);
        }
        {
            constexpr auto a1 = bml::array<copy_ctor, 2>{42, 24};
            constexpr auto a2 = bml::array<copy_ctor, 2>(a1);
            static_assert(a2[0].value == 42);
            static_assert(a2[0].copy_ctor_called);
            static_assert(a2[1].value == 24);
            static_assert(a2[1].copy_ctor_called);
        }

        // Zero length.
        {
            static_assert(bml::is_copy_constructible_v<bml::array<no_copy_ctor, 0>>);
            static_assert(bml::is_copy_constructible_v<bml::array<implicit_no_copy_ctor, 0>>);
        }
    }

    // Check that array is not copy-constructible when it is of non-zero length and its type is not
    // copy-constructible.
    {
        static_assert(!bml::is_copy_constructible_v<bml::array<no_copy_ctor, 42>>);
        static_assert(!bml::is_copy_constructible_v<bml::array<implicit_no_copy_ctor, 42>>);
    }

    // Check that array is trivially copy-constructible if its type is trivially copy-constructible
    // or if it is of zero length.
    {
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<int const volatile, 42>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<triv_copy_ctor, 42>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<triv_copy_ctor, 0>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<no_copy_ctor, 0>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::array<implicit_no_copy_ctor, 0>>);
    }
    
    // Check that array is copy-assignable if its type is copy-assignable or if it is of zero
    // length.
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>{10, 20};

            auto&& ref = (a2 = a1);

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
            bmltb_assert(&ref == &a2);
        }
        {
            auto a1 = bml::array<int volatile, 2>{42, 24};
            auto a2 = bml::array<int volatile, 2>{10, 20};

            auto&& ref = (a2 = a1);

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
            bmltb_assert(&ref == &a2);
        }

        // Constexpr context.
        static_assert([]()
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>{10, 20};

            auto&& ref = (a2 = a1);

            return a2[0] == 42 && a2[1] == 24 && &ref == &a2;
        }());

        static_assert([]()
        {
            auto a1 = bml::array<copy_assign, 2>{42, 24};
            auto a2 = bml::array<copy_assign, 2>{10, 20};

            auto&& ref = (a2 = a1);

            return a2[0].value == 42 && a2[0].copy_assign_called == true
                && a2[1].value == 24 && a2[1].copy_assign_called == true
                && &ref == &a2;
        }());

        // Zero length.
        {
            static_assert(bml::is_copy_assignable_v<bml::array<no_copy_assign, 0>>);
        }
    }

    // Check that array is not copy-assignable when it is of non-zero length and its type is not
    // copy-assignable.
    {
        static_assert(!bml::is_copy_assignable_v<bml::array<no_copy_assign, 42>>);
        static_assert(!bml::is_copy_assignable_v<bml::array<implicit_no_copy_assign, 42>>);
    }

    // Check that array is trivially copy-assignable if its type is trivially copy-assignable or if
    // it is of zero length.
    {
        static_assert(bml::is_trivially_copy_assignable_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::array<int volatile, 42>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::array<triv_copy_assign, 42>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::array<copy_assign, 0>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::array<no_copy_assign, 0>>);
    }

    // Check that array is move-constructible when its type is move-constructible or if it is of
    // zero length.
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>(bml::move(a1));

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
        }
        {
            auto a1 = bml::array<int volatile, 2>{42, 24};
            auto a2 = bml::array<int volatile, 2>(bml::move(a1));

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
        }

        // Constexpr constext.
        {
            constexpr auto a1 = bml::array<int, 2>{42, 24};
            constexpr auto a2 = bml::array<int, 2>(bml::move(a1));

            static_assert(a2[0] == 42);
            static_assert(a2[1] == 24);
        }
        {
            constexpr auto a1 = bml::array<int const, 2>{42, 24};
            constexpr auto a2 = bml::array<int const, 2>(bml::move(a1));

            static_assert(a2[0] == 42);
            static_assert(a2[1] == 24);
        }

        // Move constructors cannot bind to const, so testing for move construction when T is a
        // class type needs to be done through constexpr functions instead of though declaring
        // constexpr arrays and moving them around.
        static_assert([]()
        {
            auto a1 = bml::array<move_ctor, 2>{42, 24};
            auto a2 = bml::array<move_ctor, 2>(bml::move(a1));

            return a2[0].value == 42 && a2[0].move_ctor_called
                && a2[1].value == 24 && a2[1].move_ctor_called;
        }());

        // Zero length.
        {
            static_assert(bml::is_move_constructible_v<bml::array<no_move_ctor, 0>>);
            static_assert(bml::is_move_constructible_v<bml::array<implicit_no_move_ctor, 0>>);
        }
    }

    // Check that array is not move-constructible when it is of non-zero length and its type is not
    // move-constructible.
    {
        static_assert(!bml::is_move_constructible_v<bml::array<no_move_ctor, 42>>);
        static_assert(!bml::is_move_constructible_v<bml::array<implicit_no_move_ctor, 42>>);
    }

    // Check that array is trivially move-constructible if its type is trivially move-constructible
    // or if it is of zero length.
    {
        static_assert(bml::is_trivially_move_constructible_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::array<int const volatile, 42>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::array<triv_move_ctor, 42>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::array<triv_move_ctor, 0>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::array<no_move_ctor, 0>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::array<implicit_no_move_ctor, 0>>);
    }

    // Check that array's move constructor does not participate in overload resolution if the
    // array's type is not move-constructible.
    {
        // array is still "move-constructible" since its type is still copy-constructible - overload
        // resolution selects the copy constructor when the array is move-constructed.
        static_assert(bml::is_move_constructible_v<bml::array<copy_ctor_no_move_ctor, 3>>);

        // Not move-constructible since the array's type is both not move-constructible and not
        // copy-constructible.
        static_assert(!bml::is_move_constructible_v<bml::array<no_move_ctor, 3>>);
    }

    // Check that array is move-assignable if its type is move-assignable or if it is of zero
    // length.
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>{10, 20};

            auto&& ref = (a2 = bml::move(a1));

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
            bmltb_assert(&ref == &a2);
        }
        {
            auto a1 = bml::array<int volatile, 2>{42, 24};
            auto a2 = bml::array<int volatile, 2>{10, 20};

            auto&& ref = (a2 = bml::move(a1));

            bmltb_assert(a2[0] == 42);
            bmltb_assert(a2[1] == 24);
            bmltb_assert(&ref == &a2);
        }

        // Constexpr context.
        static_assert([]()
        {
            auto a1 = bml::array<int, 2>{42, 24};
            auto a2 = bml::array<int, 2>{10, 20};

            auto&& ref = (a2 = bml::move(a1));

            return a2[0] == 42 && a2[1] == 24 && &ref == &a2;
        }());

        static_assert([]()
        {
            auto a1 = bml::array<move_assign, 2>{42, 24};
            auto a2 = bml::array<move_assign, 2>{10, 20};

            auto&& ref = (a2 = bml::move(a1));

            return a2[0].value == 42 && a2[0].move_assign_called == true
                && a2[1].value == 24 && a2[1].move_assign_called == true
                && &ref == &a2;
        }());

        // Zero length.
        {
            static_assert(bml::is_move_assignable_v<bml::array<no_move_assign, 0>>);
        }
    }

    // Check that array is not move-assignable when it is of non-zero length and its type is not
    // move-assignable.
    {
        static_assert(!bml::is_move_assignable_v<bml::array<no_move_assign, 42>>);
        static_assert(!bml::is_move_assignable_v<bml::array<implicit_no_move_assign, 42>>);
    }

    // Check that array is trivially move-assignable if its type is trivially move-assignable or if
    // it is of zero length.
    {
        static_assert(bml::is_trivially_move_assignable_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::array<int volatile, 42>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::array<triv_move_assign, 42>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::array<move_assign, 0>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::array<no_move_assign, 0>>);
    }

    // Check that array's move constructor does not participate in overload resolution if the
    // array's type is not move-constructible.
    {
        // array is still "move-assignable" since its type is still copy-assignable - overload
        // resolution selects the move assignment operator when the array is move-assigned.
        static_assert(bml::is_move_assignable_v<bml::array<copyable_no_move_assign, 3>>);

        // Not move-assignable since the array's type is both not move-assignable and not
        // copy-assignable.
        static_assert(!bml::is_move_constructible_v<bml::array<no_move_assign, 3>>);
    }

    // Check that array is destructible if its type is destructible or if it is of zero length, and
    // that all elements' destructors are invoked.
    {
        {
            dtor::count = 0;
            {
                auto a = bml::array<dtor, 5>();
            }
            bmltb_assert(dtor::count == 5);
        }
        {
            static_assert(bml::is_destructible_v<bml::array<int, 0>>);
            static_assert(bml::is_destructible_v<bml::array<no_dtor, 0>>);
        }
    }

    // Check that array is not destructible when its type is not destructible and it is of non-zero
    // length.
    {
        static_assert(!bml::is_destructible_v<bml::array<no_dtor, 42>>);
    }

    // Check that array is trivially destructible if its type is trivially destructible or if it is
    // of zero length.
    {
        static_assert(bml::is_trivially_destructible_v<bml::array<int, 42>>);
        static_assert(bml::is_trivially_destructible_v<bml::array<triv_dtor, 42>>);
        static_assert(bml::is_trivially_destructible_v<bml::array<dtor, 0>>);
    }

    // Check that size returns the array length.
    {
        {
            constexpr auto a = bml::array<int, 5>();
            static_assert(a.size() == 5);
        }
        {
            constexpr auto a = bml::array<double, 3>{24, 42, 84.42};
            static_assert(a.size() == 3);
        }
        {
            constexpr auto a = bml::array<int, 0>();
            static_assert(a.size() == 0);
        }
    }

    // Check that max_size returns the array length.
    {
        {
            constexpr auto a = bml::array<int, 5>();
            static_assert(a.max_size() == 5);
        }
        {
            constexpr auto a = bml::array<double, 3>{24, 42, 84.42};
            static_assert(a.max_size() == 3);
        }
        {
            constexpr auto a = bml::array<int, 0>();
            static_assert(a.max_size() == 0);
        }
    }

    // Check that empty yields true only if the array is of zero length, and false otherwise.
    {
        {
            constexpr auto a = bml::array<int, 5>();
            static_assert(!a.empty());
        }
        {
            constexpr auto a = bml::array<double, 3>{24, 42, 84.42};
            static_assert(!a.empty());
        }
        {
            constexpr auto a = bml::array<int, 0>();
            static_assert(a.empty());
        }
    }

    // Check that operator[] returns a reference to the requested element.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{24, 42, 26};

            bmltb_assert(a[0] == 24);
            bmltb_assert(a[1] == 42);
            bmltb_assert(a[2] == 26);
        }
        {
            auto a = bml::array<int volatile, 3>{24, 42, 26};
            a[1] = 25;

            bmltb_assert(a[0] == 24);
            bmltb_assert(a[1] == 25);
            bmltb_assert(a[2] == 26);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{24, 42, 26};

            static_assert(a[0] == 24);
            static_assert(a[1] == 42);
            static_assert(a[2] == 26);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{24, 42, 26};
            a[1] = 25;

            return a[0] == 24 && a[1] == 25 && a[2] == 26;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            a[2].i = 1234;

            return a[0].i == 42 && a[1].i == 420 && a[2].i == 1234;
        }());
    }

    // Check that operator[] returns:
    //   1. a lvalue reference if the array is an lvalue, otherwise a rvalue reference.
    //   2. a reference with its underlying type having the same cv-qualification as the the array's
    //      type, with the array's const qualification applied to that type.
    {
        // Array is lvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>()[1]), int&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>()[1]), int const&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>()[1]), int const&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>()[1]), int const&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>()[1]), int volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>()[1]),
                int const volatile&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>()[1]), int const volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>()[1]),
                int const volatile&>);
        }

        // Array is rvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>()[1]), int&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>()[1]), int const&&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>()[1]), int const&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>()[1]), int const&&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>()[1]), int volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>()[1]),
                int const volatile&&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>()[1]), int const volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>()[1]),
                int const volatile&&>);
        }
    }

    // Check that operator[] cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_subscript_op, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_subscript_op, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_subscript_op, bml::array<default_ctor, 0>>);
        static_assert(!bml::is_detected_v<has_subscript_op, bml::array<no_default_ctor, 0>>);
    }

    // Check that member get returns a reference to the requested element.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{24, 42, 26};

            bmltb_assert(a.get<0>() == 24);
            bmltb_assert(a.get<1>() == 42);
            bmltb_assert(a.get<2>() == 26);
        }
        {
            auto a = bml::array<int volatile, 3>{24, 42, 26};
            a.get<1>() = 25;

            bmltb_assert(a.get<0>() == 24);
            bmltb_assert(a.get<1>() == 25);
            bmltb_assert(a.get<2>() == 26);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{24, 42, 26};

            static_assert(a.get<0>() == 24);
            static_assert(a.get<1>() == 42);
            static_assert(a.get<2>() == 26);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{24, 42, 26};
            a.get<1>() = 25;

            return a.get<0>() == 24 && a.get<1>() == 25 && a.get<2>() == 26;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            a.get<2>().i = 1234;

            return a.get<0>().i == 42 && a.get<1>().i == 420 && a.get<2>().i == 1234;
        }());
    }

    // Check that member get returns:
    //   1. a lvalue reference if the array is an lvalue, otherwise a rvalue reference.
    //   2. a reference with its underlying type having the same cv-qualification as the the array's
    //      type, with the array's const qualification applied to that type.
    {
        // Array is lvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()), int const&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int const&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()), int const&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()),
                int const volatile&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()),
                int const volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()),
                int const volatile&>);
        }

        // Array is rvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const&&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int const&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const&&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const volatile&&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()),
                int const volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const volatile&&>);
        }
    }

    // Check that member get cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_mem_get, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_mem_get, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_mem_get, bml::array<default_ctor, 0>>);
        static_assert(!bml::is_detected_v<has_mem_get, bml::array<no_default_ctor, 0>>);
    }

    // Check that free get returns a reference to the requested element.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{24, 42, 26};

            bmltb_assert(bml::get<0>(a) == 24);
            bmltb_assert(bml::get<1>(a) == 42);
            bmltb_assert(bml::get<2>(a) == 26);
        }
        {
            auto a = bml::array<int volatile, 3>{24, 42, 26};
            bml::get<1>(a) = 25;

            bmltb_assert(bml::get<0>(a) == 24);
            bmltb_assert(bml::get<1>(a) == 25);
            bmltb_assert(bml::get<2>(a) == 26);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{24, 42, 26};

            static_assert(bml::get<0>(a) == 24);
            static_assert(bml::get<1>(a) == 42);
            static_assert(bml::get<2>(a) == 26);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{24, 42, 26};
            bml::get<1>(a) = 25;

            return bml::get<0>(a) == 24 && bml::get<1>(a) == 25 && bml::get<2>(a) == 26;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            bml::get<2>(a).i = 1234;

            return bml::get<0>(a).i == 42 && bml::get<1>(a).i == 420 && bml::get<2>(a).i == 1234;
        }());
    }

    // Check that free get returns:
    //   1. a lvalue reference if the array is an lvalue, otherwise a rvalue reference.
    //   2. a reference with its underlying type having the same cv-qualification as the the array's
    //      type, with the array's const qualification applied to that type.
    {
        // Array is lvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()), int const&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int const&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()), int const&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()), int volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()),
                int const volatile&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().get<1>()),
                int const volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().get<1>()),
                int const volatile&>);
        }

        // Array is rvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const&&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int const&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const&&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()), int volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const volatile&&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().get<1>()),
                int const volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().get<1>()),
                int const volatile&&>);
        }
    }

    // Check that front returns a reference to the first element of the array when the array is not
    // of zero length.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{42, 25, 26};

            bmltb_assert(a.front() == 42);
        }
        {
            auto a = bml::array<int volatile, 3>{42, 25, 26};
            a.front() = 24;

            bmltb_assert(a.front() == 24);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{10, 20, 30};

            static_assert(a.front() == 10);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{42, 25, 26};
            a.front() = 24;

            return a.front() == 24;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            a.front().i = 1234;

            return a.front().i == 1234;
        }());
    }

    // Check that front returns:
    //   1. a lvalue reference if the array is an lvalue, otherwise a rvalue reference.
    //   2. a reference with its underlying type having the same cv-qualification as the the array's
    //      type, with the array's const qualification applied to that type.
    {
        // Array is lvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().front()), int&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().front()), int const&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().front()), int const&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().front()), int const&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().front()), int volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().front()),
                int const volatile&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().front()),
                int const volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().front()),
                int const volatile&>);
        }

        // Array is rvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()), int&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()),
                int const&&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()), int const&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()), int const&&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()), int volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()),
                int const volatile&&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()),
                int const volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()),
                int const volatile&&>);
        }
    }

    // Check that front cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_front, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_front, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_front, bml::array<default_ctor, 0>>);
        static_assert(!bml::is_detected_v<has_front, bml::array<no_default_ctor, 0>>);
    }

    // Check that back returns a reference to the first element of the array when the array is not
    // of zero length.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{10, 20, 42};

            bmltb_assert(a.back() == 42);
        }
        {
            auto a = bml::array<int volatile, 3>{10, 20, 42};
            a.back() = 30;

            bmltb_assert(a.back() == 30);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{10, 20, 30};

            static_assert(a.back() == 30);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{10, 25, 26};
            a.back() = 24;

            return a.back() == 24;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            a.back().i = 1234;

            return a.back().i == 1234;
        }());
    }

    // Check that back returns:
    //   1. a lvalue reference if the array is an lvalue, otherwise a rvalue reference.
    //   2. a reference with its underlying type having the same cv-qualification as the the array's
    //      type, with the array's const qualification applied to that type.
    {
        // Array is lvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().back()), int&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().back()), int const&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().back()), int const&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().back()), int const&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().back()), int volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().back()),
                int const volatile&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().back()), int const volatile&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().back()),
                int const volatile&>);
        }

        // Array is rvalue.
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().back()), int&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().back()), int const&&>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()), int const&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()), int const&&>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()), int volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()),
                int const volatile&&>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().front()),
                int const volatile&&>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().front()),
                int const volatile&&>);
        }
    }

    // Check that back cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_back, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_back, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_back, bml::array<default_ctor, 0>>);
        static_assert(!bml::is_detected_v<has_back, bml::array<no_default_ctor, 0>>);
    }

    // Check that back, front, member get, free get and operator[] all return references to the same
    // element.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int volatile, 3>{10, 20, 30};

            bmltb_assert(&a[0] == &a.get<0>());
            bmltb_assert(&a.get<0>() == &bml::get<0>(a));
            bmltb_assert(&a[1] == &a.get<1>());
            bmltb_assert(&a.get<1>() == &bml::get<1>(a));
            bmltb_assert(&a[2] == &a.get<2>());
            bmltb_assert(&a.get<2>() == &bml::get<2>(a));

            bmltb_assert(&a.front() == &a[0]);
            bmltb_assert(&a.back() == &a[2]);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{10, 20, 30};

            static_assert(&a[0] == &a.get<0>());
            static_assert(&a.get<0>() == &bml::get<0>(a));
            static_assert(&a[1] == &a.get<1>());
            static_assert(&a.get<1>() == &bml::get<1>(a));
            static_assert(&a[2] == &a.get<2>());
            static_assert(&a.get<2>() == &bml::get<2>(a));

            static_assert(&a.front() == &a[0]);
            static_assert(&a.back() == &a[2]);
        }
    }

    // Check that data returns a pointer to the first element of array's contiguous element storage.
    {
        // Non-constexpr context.
        {
            auto a = bml::array<int, 3>{20, 30, 40};

            bmltb_assert(a.data() == &a[0]);
            bmltb_assert(*a.data() == a[0]);

            bmltb_assert(a.data()[0] == 20);
            bmltb_assert(a.data()[1] == 30);
            bmltb_assert(a.data()[2] == 40);
        }
        {
            auto a = bml::array<int volatile, 3>{20, 30, 40};
            a.data()[1] = 42;

            bmltb_assert(a.data()[0] == 20);
            bmltb_assert(a.data()[1] == 42);
            bmltb_assert(a.data()[2] == 40);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array<int, 3>{20, 30, 40};

            static_assert(a.data() == &a[0]);
            static_assert(*a.data() == a[0]);

            static_assert(a.data()[0] == 20);
            static_assert(a.data()[1] == 30);
            static_assert(a.data()[2] == 40);
        }

        static_assert([]()
        {
            auto a = bml::array<int, 3>{24, 42, 26};
            a.data()[1] = 25;

            return a.data()[0] == 24 && a.data()[1] == 25 && a.data()[2] == 26;
        }());

        static_assert([]()
        {
            auto a = bml::array<no_default_ctor, 3>{42, 420, 4200};
            a.data()[2].i = 1234;

            return a.data()[0].i == 42 && a.data()[1].i == 420 && a.data()[2].i == 1234;
        }());
    }

    // Check that data returns a pointer with its underlying type having the same cv-qualification
    // as the the array's type, with the array's const qualification applied to that type.
    {
        {
            using a = bml::array<int, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().data()), int*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().data()), int*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().data()), int const*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().data()), int const*>);
        }
        {
            using a = bml::array<int const, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().data()), int const*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().data()), int const*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().data()), int const*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().data()), int const*>);
        }
        {
            using a = bml::array<int volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().data()), int volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().data()), int volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().data()),
                int const volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().data()),
                int const volatile*>);
        }
        {
            using a = bml::array<int const volatile, 2>;
            static_assert(bml::is_same_v<decltype(bml::declval<a&>().data()), int const volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a&&>().data()),
                int const volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&>().data()),
                int const volatile*>);
            static_assert(bml::is_same_v<decltype(bml::declval<a const&&>().data()),
                int const volatile*>);
        }
    }

    // Check that data cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_data, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_data, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_data, bml::array<default_ctor, 0>>);
        static_assert(!bml::is_detected_v<has_data, bml::array<no_default_ctor, 0>>);
    }

    // Check that fill fills the array with copies of its argument.
    {
        // Non-constexpr context.
        {
            auto i = 42;
            auto a = bml::array<int, 3>{10, 20, 30};
            a.fill(i);

            bmltb_assert(i == 42);
            bmltb_assert(a[0] == 42);
            bmltb_assert(a[1] == 42);
            bmltb_assert(a[2] == 42);
        }
        {
            auto volatile i = 42;
            auto a = bml::array<int volatile, 3>{10, 20, 30};

            // Check that copies are made by changing one element after calling fill, then checking
            // that no other elements nor the original object have been changed.
            a.fill(i);
            a[0] = 10;

            bmltb_assert(i == 42);
            bmltb_assert(a[0] == 10);
            bmltb_assert(a[1] == 42);
            bmltb_assert(a[2] == 42);
        }

        // Constexpr context.
        static_assert([]()
        {
            auto a = bml::array<int, 3>{10, 20, 30};
            a.fill(42);

            return a[0] == 42 && a[1] == 42 && a[2] == 42;
        }());

        static_assert([]()
        {
            auto o = no_default_ctor(42);
            auto a = bml::array<no_default_ctor, 3>{10, 20, 30};
            a.fill(o);
            a[0].i = 9000;
            
            return o.i == 42 && a[0].i == 9000 && a[1].i == 42 && a[2].i == 42;
        }());
    }

    // Check that fill cannot be called on arrays of zero length.
    {
        static_assert(!bml::is_detected_v<has_fill_int, bml::array<int, 0>>);
        static_assert(!bml::is_detected_v<has_fill_int, bml::array<int const volatile, 0>>);
        static_assert(!bml::is_detected_v<has_fill_default_ctor, bml::array<default_ctor, 0>>);
    }

    // Check that member swap swaps the array contents with the argument array's contents if the
    // array's type is swappable.
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int volatile, 3>{10, 20, 30};
            auto a2 = bml::array<int volatile, 3>{42, 43, 44};
            a1.swap(a2);

            bmltb_assert(a1[0] == 42);
            bmltb_assert(a1[1] == 43);
            bmltb_assert(a1[2] == 44);

            bmltb_assert(a2[0] == 10);
            bmltb_assert(a2[1] == 20);
            bmltb_assert(a2[2] == 30);
        }
        
        // Constexpr context.
        static_assert([]()
        {
            auto a1 = bml::array<int, 3>{10, 20, 30};
            auto a2 = bml::array<int, 3>{42, 43, 44};
            a1.swap(a2);

            return a1[0] == 42 && a1[1] == 43 && a1[2] == 44
                && a2[0] == 10 && a2[1] == 20 && a2[2] == 30;
        }());

        // Check that the user-defined swap is called if it's available.
        {
            swappee::swap_called = false;
            auto a1 = bml::array<swappee, 3>{10, 20, 30};
            auto a2 = bml::array<swappee, 3>{42, 43, 44};
            a1.swap(a2);

            bmltb_assert(swappee::swap_called);

            bmltb_assert(a1[0].value == 42);
            bmltb_assert(a1[1].value == 43);
            bmltb_assert(a1[2].value == 44);

            bmltb_assert(a2[0].value == 10);
            bmltb_assert(a2[1].value == 20);
            bmltb_assert(a2[2].value == 30);
        }

        // Zero length.
        {
            static_assert(bml::is_detected_v<has_mem_swap, bml::array<swappee, 0>>);
        }
    }

    // Check that member swap is not callable if the array's type is not swappable.
    {
        static_assert(!bml::is_detected_v<has_mem_swap, bml::array<not_swappable, 0>>);
        static_assert(!bml::is_detected_v<has_mem_swap, bml::array<not_swappable, 42>>);
    }

    // Check that free swap swaps the array contents with the argument array's contents if the
    // array's type is swappable, if it is of zero length, or if the array can be swapped with the
    // generic swap approach (i.e. swapping via move construction and assignment, regardless of
    // whether the array's type is swappable or not).
    {
        // Non-constexpr context.
        {
            auto a1 = bml::array<int volatile, 3>{10, 20, 30};
            auto a2 = bml::array<int volatile, 3>{42, 43, 44};

            using bml::swap;
            swap(a1, a2);

            bmltb_assert(a1[0] == 42);
            bmltb_assert(a1[1] == 43);
            bmltb_assert(a1[2] == 44);

            bmltb_assert(a2[0] == 10);
            bmltb_assert(a2[1] == 20);
            bmltb_assert(a2[2] == 30);
        }

        // Constexpr context.
        static_assert([]()
        {
            auto a1 = bml::array<int, 3>{10, 20, 30};
            auto a2 = bml::array<int, 3>{42, 43, 44};

            using bml::swap;
            swap(a1, a2);

            return a1[0] == 42 && a1[1] == 43 && a1[2] == 44
                && a2[0] == 10 && a2[1] == 20 && a2[2] == 30;
        }());

        // Check that the user-defined swap is called if it's available.
        {
            swappee::swap_called = false;
            auto a1 = bml::array<swappee, 3>{10, 20, 30};
            auto a2 = bml::array<swappee, 3>{42, 43, 44};
            
            using bml::swap;
            using ::swap;
            swap(a1, a2);

            bmltb_assert(swappee::swap_called);

            bmltb_assert(a1[0].value == 42);
            bmltb_assert(a1[1].value == 43);
            bmltb_assert(a1[2].value == 44);

            bmltb_assert(a2[0].value == 10);
            bmltb_assert(a2[1].value == 20);
            bmltb_assert(a2[2].value == 30);
        }

        // Zero length.
        {
            static_assert(bml::is_swappable_v<bml::array<swappee, 0>>);
            static_assert(bml::is_swappable_v<bml::array<not_swappable, 0>>);
        }

        // Check that the generic swapping approach can be used even if type is not swappable as
        // as long as the array is move-constructible and move-assignable.
        {
            static_assert(bml::is_swappable_v<bml::array<not_swappable, 42>>);
        }
    }

    // Check that free swap is not callable if array's type is not swappable, and the array itself
    // is not move-constructible or move-assignable (so that the "generic" swap cannot be used).
    {
        static_assert(!bml::is_swappable_v<bml::array<not_swappable_or_movable, 42>>);
    }

    // Check that tuple_size yields the array length.
    {
        static_assert(bml::tuple_size<bml::array<int, 0>>::value == 0);
        static_assert(bml::tuple_size_v<bml::array<int, 0>> == 0);
        static_assert(bml::tuple_size<bml::array<int, 5>>::value == 5);
        static_assert(bml::tuple_size_v<bml::array<int, 5>> == 5);
        static_assert(bml::tuple_size<bml::array<int, 5> const volatile>::value == 5);
        static_assert(bml::tuple_size_v<bml::array<int, 5> const volatile> == 5);
    }

    // Check that tuple_elem yields the array's type.
    {
        using a = bml::array<int, 3>;

        static_assert(bml::is_same_v<typename bml::tuple_element<0, a>::type, int>);
        static_assert(bml::is_same_v<typename bml::tuple_element<1, a>::type, int>);
        static_assert(bml::is_same_v<typename bml::tuple_element<2, a>::type, int>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<0, a>, int>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<1, a>, int>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<2, a>, int>);

        static_assert(bml::is_same_v<typename bml::tuple_element<0, a const volatile>::type,
            int const volatile>);
        static_assert(bml::is_same_v<typename bml::tuple_element<1, a const volatile>::type,
            int const volatile>);
        static_assert(bml::is_same_v<typename bml::tuple_element<2, a const volatile>::type,
            int const volatile>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<0, a const volatile>,
            int const volatile>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<1, a const volatile>,
            int const volatile>);
        static_assert(bml::is_same_v<bml::tuple_element_ty<2, a const volatile>,
            int const volatile>);
    }

    // Check that when array is initialized with N arguments of type T, its explicit deduction guide
    // deduces an array of length N containing type T after removing its cv-qualification.
    {
        // Non-constexpr context.
        {
            auto a = bml::array{42};

            static_assert(bml::is_same_v<decltype(a), bml::array<int, 1>>);
        }
        {
            auto const volatile i1 = 10;
            auto const volatile i2 = 20;
            auto a = bml::array{i1, i2};

            static_assert(bml::is_same_v<decltype(a), bml::array<int, 2>>);
        }

        // Constexpr context.
        {
            constexpr auto a = bml::array{42};

            static_assert(bml::is_same_v<decltype(a), bml::array<int, 1> const>);
        }
        {
            constexpr auto i1 = 10;
            constexpr auto i2 = 20;
            constexpr auto a = bml::array{i1, i2};

            static_assert(bml::is_same_v<decltype(a), bml::array<int, 2> const>);
        }
        {
            constexpr auto a = bml::array{42L, 122L, 102934L};

            static_assert(bml::is_same_v<decltype(a), bml::array<long, 3> const>);
        }
    }

    // Check that array's implicit deduction guide applies when array is initialized with another
    // array.
    {
        auto a1 = bml::array<int, 2>{42, 1029};
        auto a2 = bml::array(a1);
        static_assert(bml::is_same_v<decltype(a2), decltype(a1)>);
        static_assert(bml::is_same_v<decltype(a2), bml::array<int, 2>>);
    }

    return 0;
}
