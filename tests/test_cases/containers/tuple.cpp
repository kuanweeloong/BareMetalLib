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
#include <bml/containers/tuple.hpp>
#include <bml/type_traits/is_constructible.hpp>
#include <bml/type_traits/is_explicitly_constructible.hpp>
#include <bml/type_traits/is_default_constructible.hpp>
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
#include <bml/type_traits/is_swappable.hpp>
#include <bml/utilities/move.hpp>
#include <bml/utilities/declval.hpp>

struct multiply
{
    int value;
    
    constexpr multiply(int a, int b) : value(a * b) {}
};

struct default_ctor
{
	int i;
	
	constexpr default_ctor() : i(42) {}
};

struct explicit_default_ctor
{
	int i;
	
	constexpr explicit explicit_default_ctor() : i(42) {}
};

struct no_default_ctor
{
	no_default_ctor() = delete;
	explicit no_default_ctor(int) {}
};

struct implicit_from_int
{
	int value;
	
	constexpr implicit_from_int(int v) : value(v) {}
};

struct explicit_from_int
{
	int value;
	
	explicit constexpr explicit_from_int(int v) : value(v) {}
};

constexpr auto global_i = 42;
constexpr auto global_c = 'a';

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

struct explicit_copy_ctor
{
	constexpr explicit_copy_ctor() = default;
    constexpr explicit explicit_copy_ctor(explicit_copy_ctor const&) = default;
    
	explicit_copy_ctor(explicit_copy_ctor&&) = delete;
    auto operator=(explicit_copy_ctor const&) -> explicit_copy_ctor& = delete;
    auto operator=(explicit_copy_ctor&&) -> explicit_copy_ctor& = delete;
};

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
    auto operator=(copy_assign&&) -> copy_assign& = delete;
};

struct triv_copy_assign
{
    int value;
    
    constexpr triv_copy_assign(int i) : value(i) {}
	
    auto operator=(triv_copy_assign const&) -> triv_copy_assign& = default;
    
	triv_copy_assign(triv_copy_assign const&) = delete;
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
    auto operator=(move_assign const&) -> move_assign& = delete;
};

struct triv_move_assign
{
    int value;
    
    constexpr triv_move_assign(int i) : value(i) {}
    
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

template <int>
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

template <::ptrdiff_t I, typename Tuple, typename Expected>
constexpr auto check_tuple_element() noexcept -> void
{
    static_assert(bml::is_same_v<typename bml::tuple_element<I, Tuple>::type, Expected>);
    static_assert(bml::is_same_v<bml::tuple_element_ty<I, Tuple>, Expected>);
    
    static_assert(bml::is_same_v<typename bml::tuple_element<I, Tuple const>::type,
		Expected const>);
    static_assert(bml::is_same_v<bml::tuple_element_ty<I, Tuple const>,
		Expected const>);
    
    static_assert(bml::is_same_v<typename bml::tuple_element<I, Tuple volatile>::type,
        Expected volatile>);
    static_assert(bml::is_same_v<bml::tuple_element_ty<I, Tuple volatile>,
        Expected volatile>);
    
    static_assert(bml::is_same_v<typename bml::tuple_element<I, Tuple const volatile>::type,
        Expected const volatile>);
    static_assert(bml::is_same_v<bml::tuple_element_ty<I, Tuple const volatile>,
        Expected const volatile>);
}

template <typename Tuple, ::ptrdiff_t N>
constexpr auto check_tuple_size() noexcept -> void
{
    static_assert(bml::tuple_size<Tuple>::value == N);
    static_assert(bml::tuple_size_v<Tuple> == N);
    
    static_assert(bml::tuple_size<Tuple const>::value == N);
    static_assert(bml::tuple_size_v<Tuple const> == N);
    
    static_assert(bml::tuple_size<Tuple volatile>::value == N);
    static_assert(bml::tuple_size_v<Tuple volatile> == N);
    
    static_assert(bml::tuple_size<Tuple const volatile>::value == N);
    static_assert(bml::tuple_size_v<Tuple const volatile> == N);
}

template <typename Tuple, ::ptrdiff_t I, typename Expected>
constexpr auto check_member_get_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::declval<Tuple&>().template get<I>()),
        Expected&>);
    static_assert(bml::is_same_v<decltype(bml::declval<Tuple const&>().template get<I>()),
        Expected const&>);
    
    static_assert(bml::is_same_v<decltype(bml::declval<Tuple>().template get<I>()),
        Expected&&>);
    static_assert(bml::is_same_v<decltype(bml::declval<Tuple const>().template get<I>()),
        Expected const&&>);
}

template <typename Tuple, ::ptrdiff_t I, typename Expected>
constexpr auto check_free_get_type() noexcept -> void
{
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<Tuple&>())),
        Expected&>);
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<Tuple const&>())),
        Expected const&>);
    
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<Tuple>())),
        Expected&&>);
    static_assert(bml::is_same_v<decltype(bml::get<I>(bml::declval<Tuple const>())),
        Expected const&&>);
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

struct empty {};

auto test_main() noexcept -> int
{
	// Check that tuple can be default constructed when its elements can be default constructed.
	{
		{
			static_cast<void>(bml::tuple<>());
		}
		{
			static_cast<void>(bml::tuple<int[3]>());
		}
		{
			constexpr auto t = bml::tuple<int>();
			static_assert(t.get<0>() == 0);
		}
		{
			constexpr auto t = bml::tuple<int, default_ctor>();
			static_assert(t.get<0>() == 0);
			static_assert(t.get<1>().i == 42);
		}
		{
			constexpr auto t = bml::tuple<int, default_ctor const, char const*, int>();
			static_assert(t.get<0>() == 0);
			static_assert(t.get<1>().i == 42);
			static_assert(t.get<2>() == nullptr);
			static_assert(t.get<3>() == 0);
		}
	}
	
	// Check that tuple's default constructor is explicit when at least one of its elements is not
	// implicitly default-constructible.
	{
		static_assert(bml::is_explicitly_constructible_v<bml::tuple<explicit_default_ctor>>);
		static_assert(bml::is_explicitly_constructible_v<bml::tuple<int, explicit_default_ctor>>);
		static_assert(bml::is_explicitly_constructible_v<bml::tuple<int, explicit_default_ctor,
			int>>);
	}
	
	// Check that tuple cannot be default constructed when at least one of its elements is not
	// default-constructible.
	{
		static_assert(!bml::is_default_constructible_v<bml::tuple<no_default_ctor>>);
		static_assert(!bml::is_default_constructible_v<bml::tuple<no_default_ctor, int>>);
		static_assert(!bml::is_default_constructible_v<bml::tuple<no_default_ctor, int, int>>);
		
		static_assert(!bml::is_default_constructible_v<bml::tuple<int&, int const&, int volatile&,
			int const volatile&, int&&, int const&&, int volatile&&, int const volatile&&>>);
	}
	
	// Check that tuple can be constructed via the element-wise converting constructor when all its
	// elements are constructible from its corresponding argument.
	{
		{
			constexpr auto t = bml::tuple<int>(42);
			static_assert(t.get<0>() == 42);
		}
		{
			constexpr auto i = 42;
			constexpr auto t = bml::tuple<int, int>(i, 500);
			static_assert(t.get<0>() == 42);
			static_assert(t.get<1>() == 500);
		}
		{
			constexpr auto t = bml::tuple<int, void const*, char*, int const&>(42, &global_i,
				nullptr, global_i);
			static_assert(t.get<0>() == 42);
			static_assert(t.get<1>() == &global_i);
			static_assert(t.get<2>() == nullptr);
			static_assert(&(t.get<3>()) == &global_i);
		}
		{
			constexpr auto c = copy_ctor(200);
			constexpr auto t = bml::tuple<implicit_from_int, copy_ctor, move_ctor>(42, c,
				move_ctor(500));
			
			static_assert(t.get<0>().value == 42);
			static_assert(t.get<1>().value == 200);
			static_assert(t.get<1>().copy_ctor_called);
			static_assert(t.get<2>().value == 500);
			static_assert(t.get<2>().move_ctor_called);
		}
		{
			bmltb_assert(bml::tuple<int&&>(42).get<0>() == 42);
		}
	}
	
	// Check that tuple cannot be constructed via the element-wise converting constructor if at
	// least one element is not constructible from its corresponding constructor argument.
	{
		static_assert(!bml::is_constructible_v<bml::tuple<int&>, int>);
		static_assert(!bml::is_constructible_v<bml::tuple<int&&>, int&>);
		static_assert(!bml::is_constructible_v<bml::tuple<multiply>, int>);
		static_assert(!bml::is_constructible_v<bml::tuple<default_ctor>, int>);
		static_assert(!bml::is_constructible_v<bml::tuple<no_copy_ctor>, no_copy_ctor const&>);
		static_assert(!bml::is_constructible_v<bml::tuple<no_move_ctor>, no_move_ctor>);
		
		static_assert(!bml::is_constructible_v<bml::tuple<int&&, int, char>,
			int&, int, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, int&, char>,
			int&, int, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int&, multiply, int>,
			int, multiply const&, multiply&&>);
		static_assert(!bml::is_constructible_v<bml::tuple<int&, multiply, int, multiply>,
			int, int, int, int>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, default_ctor, char>,
			int, char, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, no_copy_ctor, char>,
			int, no_copy_ctor const&, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, no_move_ctor, char>,
			int, no_move_ctor&&, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int&&, no_copy_ctor, no_move_ctor>,
			int, no_copy_ctor const&, no_move_ctor&&>);
		static_assert(!bml::is_constructible_v<bml::tuple<int&&, no_copy_ctor, multiply>,
			int, no_copy_ctor const&, int>);
	}
	
	// Check that tuple's element-wise constructor is explicit when at least one of its elements has
	// is explicitly constructible from its corresponding constructor argument.
	{
		static_assert(bml::is_explicitly_constructible_v<bml::tuple<explicit_from_int>,
			int>);
		static_assert(bml::is_explicitly_constructible_v<bml::tuple<explicit_copy_ctor>,
			explicit_copy_ctor const&>);
		
		static_assert(bml::is_explicitly_constructible_v<
			bml::tuple<copy_ctor, explicit_from_int, int>,
			copy_ctor const&, int, int>);
		static_assert(bml::is_explicitly_constructible_v<
			bml::tuple<move_ctor, explicit_copy_ctor, int>,
			move_ctor&&, explicit_copy_ctor const&, int const&>);
	}
	
	// Check that tuple's the element-wise converting constructor does not participate in overload
	// resolution if the number of arguments passed to the constructor is not the same as the number
	// of elements.
	{
		static_assert(!bml::is_constructible_v<bml::tuple<int>, int, int>);
		
		static_assert(!bml::is_constructible_v<bml::tuple<int, char>, int>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, char>, int, int, char, char>);
		
		static_assert(!bml::is_constructible_v<bml::tuple<int, char, char>, char>);
		static_assert(!bml::is_constructible_v<bml::tuple<int, char, char>, int, int, char, char>);
	}
	
	// Check that tuple is copy-constructible if all its elements are copy-constructible.
	{
		// Non-constexpr context.
		{
			// Just checking that no compile error occurs over here...
			auto t1 = bml::tuple<>();
			static_cast<void>(bml::tuple<>(t1));
		}
		{
			auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(t1);
			
			bmltb_assert(t2.get<0>() == 42);
		}
		{
			auto t1 = bml::tuple<int const volatile, char>(42, 'a');
			auto t2 = bml::tuple<int const volatile, char>(t1);
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 'a');
		}
		{
			auto i = 100;
			auto t1 = bml::tuple<int, char, int, int&, int const volatile&>(42, 'a', 500, i, i);
			auto t2 = bml::tuple<int, char, int, int&, int const volatile&>(t1);
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 'a');
			bmltb_assert(t2.get<2>() == 500);
			bmltb_assert(&(t2.get<3>()) == &i);
			bmltb_assert(&(t2.get<4>()) == &i);
		}
		{
			auto t1 = bml::tuple<copy_ctor>(42);
			auto t2 = bml::tuple<copy_ctor>(t1);
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().copy_ctor_called);
		}
		{
			auto c = 'a';
			auto t1 = bml::tuple<int volatile, char const&, copy_ctor const, copy_ctor>(42, c, 500,
				8192);
			auto t2 = bml::tuple<int volatile, char const&, copy_ctor const, copy_ctor>(t1);
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(&(t2.get<1>()) == &c);
			bmltb_assert(t2.get<2>().value == 500);
			bmltb_assert(t2.get<2>().copy_ctor_called);
			bmltb_assert(t2.get<3>().value == 8192);
			bmltb_assert(t2.get<3>().copy_ctor_called);
		}
		
		// Constexpr context.
		{
			// Just checking that no compile error occurs over here...
			constexpr auto t1 = bml::tuple<>();
			static_cast<void>(bml::tuple<>(t1));
		}
		{
			constexpr auto t1 = bml::tuple<int>(42);
			constexpr auto t2 = bml::tuple<int>(t1);
			
			static_assert(t2.get<0>() == 42);
		}
		{
			constexpr auto t1 = bml::tuple<int const, char>(42, 'a');
			constexpr auto t2 = bml::tuple<int const, char>(t1);
			
			static_assert(t2.get<0>() == 42);
			static_assert(t2.get<1>() == 'a');
		}
		{
			constexpr auto t1 = bml::tuple<int, char, int, int const&>(42, 'a', 500, global_i);
			constexpr auto t2 = bml::tuple<int, char, int, int const&>(t1);
			
			static_assert(t2.get<0>() == 42);
			static_assert(t2.get<1>() == 'a');
			static_assert(t2.get<2>() == 500);
			static_assert(&(t2.get<3>()) == &global_i);
		}
		{
			constexpr auto t1 = bml::tuple<copy_ctor>(42);
			constexpr auto t2 = bml::tuple<copy_ctor>(t1);
			
			static_assert(t2.get<0>().value == 42);
			static_assert(t2.get<0>().copy_ctor_called);
		}
		{
			constexpr auto t1 = bml::tuple<int const, copy_ctor>(42, 500);
			constexpr auto t2 = bml::tuple<int const, copy_ctor>(t1);
			
			static_assert(t2.get<0>() == 42);
			static_assert(t2.get<1>().value == 500);
			static_assert(t2.get<1>().copy_ctor_called);
		}
		{
			constexpr auto t1 = bml::tuple<int, char const&, copy_ctor const, copy_ctor const>(42,
				global_c, 10, 500);
			constexpr auto t2 = bml::tuple<int, char const&, copy_ctor const, copy_ctor const>(t1);
			
			static_assert(t2.get<0>() == 42);
			static_assert(&(t2.get<1>()) == &global_c);
			static_assert(t2.get<2>().value == 10);
			static_assert(t2.get<2>().copy_ctor_called);
			static_assert(t2.get<3>().value == 500);
			static_assert(t2.get<3>().copy_ctor_called);
		}
	}
	
	// Check that tuple is not copy-constructible if at least one element is not copy-constructible.
	{
		static_assert(!bml::is_copy_constructible_v<bml::tuple<int&&>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<int const&&>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::tuple<implicit_no_copy_ctor>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<triv_copy_ctor const volatile>>);
		
		static_assert(!bml::is_copy_constructible_v<bml::tuple<copy_ctor, int, int&&>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<copy_ctor, int, int const&&>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<copy_ctor, int, no_copy_ctor>>);
        static_assert(!bml::is_copy_constructible_v<bml::tuple<copy_ctor, int, 
			implicit_no_copy_ctor>>);
		static_assert(!bml::is_copy_constructible_v<bml::tuple<copy_ctor, int, 
			triv_copy_ctor const volatile>>);
	}
	
	// Check that tuple is trivially copy-constructible if all elements are trivially
	// copy-constructible.
	{
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int const volatile>>);
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int&>>);
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int const volatile&>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<triv_copy_ctor>>);
        static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<triv_copy_ctor const>>);
		
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int, char const, int&,
			int const volatile>>);
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int, char const, int&,
			int const volatile&>>);
		static_assert(bml::is_trivially_copy_constructible_v<bml::tuple<int, char const, int&,
			triv_copy_ctor const>>);
        
        static_assert(!bml::is_trivially_copy_constructible_v<bml::tuple<copy_ctor>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::tuple<copy_ctor volatile>>);
		static_assert(!bml::is_trivially_copy_constructible_v<bml::tuple<int, copy_ctor,
			char const>>);
        static_assert(!bml::is_trivially_copy_constructible_v<bml::tuple<int, copy_ctor volatile,
			char const>>);
	}
	
	// Check that tuple can be copy-assigned if all elements are copy-assignable.
	{
		// Non-constexpr context.
		{
			auto t1 = bml::tuple<>();
			auto t2 = bml::tuple<>();
			
			auto&& ref = (t2 = t1);
			
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(500);
			
			auto&& ref = (t2 = t1);
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(&ref == &t2);
		}
		{
			auto i = 100;
			auto j = 200;
			auto t1 = bml::tuple<int, int, char, int&, int volatile&>(42, 420, 'a', i, i);
			auto t2 = bml::tuple<int, int, char, int&, int volatile&>(500, 1530, 'x', j, j);
			
			auto&& ref = (t2 = t1);
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 420);
			bmltb_assert(t2.get<2>() == 'a');
			bmltb_assert(&(t2.get<3>()) == &i);
			bmltb_assert(&(t2.get<4>()) == &i);
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<copy_assign>(42);
			auto t2 = bml::tuple<copy_assign>(500);
			
			auto&& ref = (t2 = t1);
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().copy_assign_called);
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<copy_assign volatile, double, copy_assign volatile>(
				42, 10.58, 500);
			auto t2 = bml::tuple<copy_assign volatile, double, copy_assign volatile>(
				15850, 42.42, 3);
			
			auto&& ref = (t2 = t1);
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().copy_assign_called);
			bmltb_assert(t2.get<1>() == 10.58);
			bmltb_assert(t2.get<2>().value == 500);
			bmltb_assert(t2.get<2>().copy_assign_called);
			bmltb_assert(&ref == &t2);
		}
		{
			// Jump through some hoops to ensure that stored rvalue references do not dangle...
			auto check = [](int&& i1, int&& i2)
			{
				auto t1 = bml::tuple<int&&>(bml::move(i1));
				auto t2 = bml::tuple<int&&>(bml::move(i2));
				
				auto&& ref = (t2 = t1);
				
				return &ref == &t2 && t2.get<0>() == 42;
			};
			
			auto check_volatile = [](int volatile&& i1, int volatile&& i2)
			{
				auto t1 = bml::tuple<int volatile&&>(bml::move(i1));
				auto t2 = bml::tuple<int volatile&&>(bml::move(i2));
				
				auto&& ref = (t2 = t1);
				
				return &ref == &t2 && t2.get<0>() == 42;
			};
			
			bmltb_assert(check(42, 24));
			bmltb_assert(check_volatile(42, 24));
		}
		
		// Constexpr context
		static_assert([]()
		{
			auto t1 = bml::tuple<>();
			auto t2 = bml::tuple<>();
			
			auto&& ref = (t2 = t1);
			
			return &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(500);
			
			auto&& ref = (t2 = t1);
			
			return t2.get<0>() == 42 && &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto i = 100;
			auto j = 1;
			auto t1 = bml::tuple<int, int, char, int&>(42, 420, 'a', i);
			auto t2 = bml::tuple<int, int, char, int&>(500, 1530, 'x', j);
			
			auto&& ref = (t2 = t1);
			
			return t2.get<0>() == 42
				&& t2.get<1>() == 420
				&& t2.get<2>() == 'a'
				&& &(t2.get<3>()) == &i
				&& &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<copy_assign>(42);
			auto t2 = bml::tuple<copy_assign>(500);
			
			auto&& ref = (t2 = t1);
			
			return t2.get<0>().value == 42
				&& t2.get<0>().copy_assign_called
				&& &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<copy_assign, double, copy_assign>(42, 10.58, 500);
			auto t2 = bml::tuple<copy_assign, double, copy_assign>(15850, 42.42, 3);
			
			auto&& ref = (t2 = t1);
			
			return t2.get<0>().value == 42
				&& t2.get<0>().copy_assign_called
				&& t2.get<1>() == 10.58
				&& t2.get<2>().value == 500
				&& t2.get<2>().copy_assign_called
				&& &ref == &t2;
		}());
		
		static_assert([](int&& i1, int&& i2)
		{
			auto t1 = bml::tuple<int&&>(bml::move(i1));
			auto t2 = bml::tuple<int&&>(bml::move(i2));
			
			auto&& ref = (t2 = t1);
			
			return t2.get<0>()== 42 && &ref == &t2;
		}(42, 24));
	}
	
	// Check that tuple is not copy-assignable if at least one element is not copy-assignable.
	{
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const&>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const&&>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<copy_assign const>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<implicit_no_copy_assign>>);
		
		static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			int const>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			int const&>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			int const&&>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			copy_assign const>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			no_copy_assign>>);
        static_assert(!bml::is_copy_assignable_v<bml::tuple<char, copy_assign,
			implicit_no_copy_assign>>);
	}
	
	// Check that tuple is trivially copy-assignable if all elements are trivially copy-assignable.
	{
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<int>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<int volatile>>);
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<int&>>);
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<int&&>>);
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<int volatile&&>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<triv_copy_assign>>);
		
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<char, int,
			int&>>);
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<char, int&&,
			int&>>);
		static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<char, int volatile&&,
			int volatile&>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<char, int volatile,
			triv_copy_assign>>);
        static_assert(bml::is_trivially_copy_assignable_v<bml::tuple<char, triv_copy_assign,
			triv_copy_assign>>);
		
        static_assert(!bml::is_trivially_copy_assignable_v<bml::tuple<copy_assign>>);
		static_assert(!bml::is_trivially_copy_assignable_v<bml::tuple<triv_copy_assign,
			copy_assign>>);
		static_assert(!bml::is_trivially_copy_assignable_v<bml::tuple<int, copy_assign,
			triv_copy_assign>>);
	}
	
	// Check that tuple can be move-constructed if all elements are move-constructible.
	{
		// Non-constexpr context.
		{
			// Just checking that no compile error occurs over here...
			auto t1 = bml::tuple<>();
			static_cast<void>(bml::tuple<>(bml::move(t1)));
		}
		{
            auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
        }
		{
			auto t1 = bml::tuple<int const volatile, char>(42, 'a');
			auto t2 = bml::tuple<int const volatile, char>(bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 'a');
		}
		{
			auto i = 100;
			auto t1 = bml::tuple<int, char, int, int&, int const volatile&>(42, 'a', 500, i, i);
			auto t2 = bml::tuple<int, char, int, int&, int const volatile&>(bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 'a');
			bmltb_assert(t2.get<2>() == 500);
			bmltb_assert(&(t2.get<3>()) == &i);
			bmltb_assert(&(t2.get<4>()) == &i);
		}
		{
			auto t1 = bml::tuple<move_ctor>(42);
			auto t2 = bml::tuple<move_ctor>(bml::move(t1));
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().move_ctor_called);
		}
		{
			auto t1 = bml::tuple<int volatile, char, move_ctor volatile, move_ctor>(42, 'a', 10, 8);
			auto t2 = bml::tuple<int volatile, char, move_ctor volatile, move_ctor>(bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 'a');
			bmltb_assert(t2.get<2>().value == 10);
			bmltb_assert(t2.get<2>().move_ctor_called);
			bmltb_assert(t2.get<3>().value == 8);
			bmltb_assert(t2.get<3>().move_ctor_called);
		}
		{
			bmltb_assert(bml::tuple<int&&>(bml::tuple<int&&>(42)).get<0>() == 42);
			bmltb_assert(bml::tuple<int const&&>(bml::tuple<int const&&>(42)).get<0>() == 42);
			bmltb_assert(bml::tuple<int volatile&&>(bml::tuple<int volatile&&>(42)).get<0>() == 42);
			bmltb_assert(bml::tuple<int const volatile&&>(bml::tuple<int const volatile&&>(42))
				.get<0>() == 42);
		}
		
		// Constexpr context.
		{
			// Just checking that no compile error occurs over here...
			constexpr auto t1 = bml::tuple<>();
			static_cast<void>(bml::tuple<>(bml::move(t1)));
		}
		{
            constexpr auto t1 = bml::tuple<int>(42);
			constexpr auto t2 = bml::tuple<int>(bml::move(t1));
			
			static_assert(t2.get<0>() == 42);
        }
		{
			constexpr auto t1 = bml::tuple<int const, char>(42, 'a');
			constexpr auto t2 = bml::tuple<int const, char>(bml::move(t1));
			
			static_assert(t2.get<0>() == 42);
			static_assert(t2.get<1>() == 'a');
		}
		{
			constexpr auto t1 = bml::tuple<int, char, int, int const&>(42, 'a', 500, global_i);
			constexpr auto t2 = bml::tuple<int, char, int, int const&>(bml::move(t1));
			
			static_assert(t2.get<0>() == 42);
			static_assert(t2.get<1>() == 'a');
			static_assert(t2.get<2>() == 500);
			static_assert(&(t2.get<3>()) == &global_i);
		}
		{
			static_assert(bml::tuple<int&&>(bml::tuple<int&&>(42)).get<0>() == 42);
			static_assert(bml::tuple<int const&&>(bml::tuple<int const&&>(42)).get<0>() == 42);
		}
		
		// Move constructors cannot bind to const, so testing for move construction when T is a
		// class type needs to be done through constexpr functions instead of though declaring
		// constexpr tuples and moving them around.
		static_assert([]()
		{
			auto t1 = bml::tuple<move_ctor>(42);
			auto t2 = bml::tuple<move_ctor>(bml::move(t1));
			
			return t2.get<0>().value == 42 && t2.get<0>().move_ctor_called;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<int, move_ctor, move_ctor>(42, 10, 8182);
			auto t2 = bml::tuple<int, move_ctor, move_ctor>(bml::move(t1));
			
			return t2.get<0>() == 42
			&& t2.get<1>().value == 10
			&& t2.get<1>().move_ctor_called
			&& t2.get<2>().value == 8182
			&& t2.get<2>().move_ctor_called;
		}());
	}
	
	// Check that the move constructor for an element does not participate in overload resolution if
	// that element is not move-constructible, and that the containing tuple is still
	// move-constructible if all elements are copy or move constructible.
	{
		// tuple is still "move-constructible" since non-movable elements are still copy-
		// constructible - overload resolution selects the copy constructor for those elements.
        static_assert(bml::is_move_constructible_v<bml::tuple<copy_ctor_no_move_ctor>>);
		static_assert(bml::is_move_constructible_v<bml::tuple<copy_ctor_no_move_ctor,
			copy_ctor_no_move_ctor>>);
		static_assert(bml::is_move_constructible_v<bml::tuple<copy_ctor_no_move_ctor, int,
			move_ctor>>);
        
        // Not move-constructible since at least one element is both not move-constructible and not
		// copy-constructible.
        static_assert(!bml::is_move_constructible_v<bml::tuple<no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::tuple<implicit_no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::tuple<triv_move_ctor const>>);
		
		static_assert(!bml::is_move_constructible_v<bml::tuple<int, copy_ctor_no_move_ctor,
			no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::tuple<int, move_ctor,
			implicit_no_move_ctor>>);
        static_assert(!bml::is_move_constructible_v<bml::tuple<int, char, move_ctor,
			triv_move_ctor const>>);
	}
	
	// Check that tuple is trivially move-constructible if all elements are trivially move or copy
	// constructible.
	{
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int volatile>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int&>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int const&>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int&&>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int const volatile&&>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::tuple<triv_move_ctor>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<triv_copy_ctor>>);
		
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, int, char>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, int&, char>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, int const&, char>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, int,
			char&&>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, int,
			char const volatile&&>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int, triv_move_ctor,
			triv_copy_ctor>>);
        static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int volatile,
			triv_move_ctor, triv_move_ctor>>);
		static_assert(bml::is_trivially_move_constructible_v<bml::tuple<int volatile,
			triv_copy_ctor, triv_copy_ctor>>);
        
        static_assert(!bml::is_trivially_move_constructible_v<bml::tuple<move_ctor>>);
		static_assert(!bml::is_trivially_move_constructible_v<bml::tuple<copy_ctor>>);
		static_assert(!bml::is_trivially_move_constructible_v<bml::tuple<int, move_ctor,
			triv_move_ctor>>);
		static_assert(!bml::is_trivially_move_constructible_v<bml::tuple<char, copy_ctor,
			triv_move_ctor>>);
	}
	
	// Check that tuple can be move-assigned if all elements are move-assignable.
	{
		// Non-constexpr context.
		{
			auto t1 = bml::tuple<>();
			auto t2 = bml::tuple<>();
			
			auto&& ref = (t2 = bml::move(t1));
			
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(500);
			
			auto&& ref = (t2 = bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(&ref == &t2);
		}
		{
			auto i = 100;
			auto j = 200;
			auto t1 = bml::tuple<int, int, char, int&, int volatile&>(42, 420, 'a', i, i);
			auto t2 = bml::tuple<int, int, char, int&, int volatile&>(500, 1530, 'x', j, j);
			
			auto&& ref = (t2 = bml::move(t1));
			
			bmltb_assert(t2.get<0>() == 42);
			bmltb_assert(t2.get<1>() == 420);
			bmltb_assert(t2.get<2>() == 'a');
			bmltb_assert(&(t2.get<3>()) == &i);
			bmltb_assert(&(t2.get<4>()) == &i);
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<move_assign>(42);
			auto t2 = bml::tuple<move_assign>(500);
			
			auto&& ref = (t2 = bml::move(t1));
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().move_assign_called);
			bmltb_assert(&ref == &t2);
		}
		{
			auto t1 = bml::tuple<move_assign volatile, double, move_assign volatile>(
				42, 10.58, 500);
			auto t2 = bml::tuple<move_assign volatile, double, move_assign volatile>(
				15850, 42.42, 3);
			
			auto&& ref = (t2 = bml::move(t1));
			
			bmltb_assert(t2.get<0>().value == 42);
			bmltb_assert(t2.get<0>().move_assign_called);
			bmltb_assert(t2.get<1>() == 10.58);
			bmltb_assert(t2.get<2>().value == 500);
			bmltb_assert(t2.get<2>().move_assign_called);
			bmltb_assert(&ref == &t2);
		}
		{
			// Jump through some hoops to ensure that stored rvalue references do not dangle...
			auto check = [](int&& i1, int&& i2)
			{
				auto t1 = bml::tuple<int&&>(bml::move(i1));
				auto t2 = bml::tuple<int&&>(bml::move(i2));
				
				auto&& ref = (t2 = bml::move(t1));
				
				return &ref == &t2 && t2.get<0>() == 42;
			};
			
			auto check_volatile = [](int volatile&& i1, int volatile&& i2)
			{
				auto t1 = bml::tuple<int volatile&&>(bml::move(i1));
				auto t2 = bml::tuple<int volatile&&>(bml::move(i2));
				
				auto&& ref = (t2 = bml::move(t1));
				
				return &ref == &t2 && t2.get<0>() == 42;
			};
			
			bmltb_assert(check(42, 24));
			bmltb_assert(check_volatile(42, 24));
		}
		
		// Constexpr context
		static_assert([]()
		{
			auto t1 = bml::tuple<>();
			auto t2 = bml::tuple<>();
			
			auto&& ref = (t2 = bml::move(t1));
			
			return &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<int>(42);
			auto t2 = bml::tuple<int>(500);
			
			auto&& ref = (t2 = bml::move(t1));
			
			return t2.get<0>() == 42 && &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto i = 100;
			auto j = 1;
			auto t1 = bml::tuple<int, int, char, int&>(42, 420, 'a', i);
			auto t2 = bml::tuple<int, int, char, int&>(500, 1530, 'x', j);
			
			auto&& ref = (t2 = bml::move(t1));
			
			return t2.get<0>() == 42
				&& t2.get<1>() == 420
				&& t2.get<2>() == 'a'
				&& &(t2.get<3>()) == &i
				&& &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<move_assign>(42);
			auto t2 = bml::tuple<move_assign>(500);
			
			auto&& ref = (t2 = bml::move(t1));
			
			return t2.get<0>().value == 42
				&& t2.get<0>().move_assign_called
				&& &ref == &t2;
		}());
		
		static_assert([]()
		{
			auto t1 = bml::tuple<move_assign, double, move_assign>(42, 10.58, 500);
			auto t2 = bml::tuple<move_assign, double, move_assign>(15850, 42.42, 3);
			
			auto&& ref = (t2 = bml::move(t1));
			
			return t2.get<0>().value == 42
				&& t2.get<0>().move_assign_called
				&& t2.get<1>() == 10.58
				&& t2.get<2>().value == 500
				&& t2.get<2>().move_assign_called
				&& &ref == &t2;
		}());
		
		static_assert([](int&& i1, int&& i2)
		{
			auto t1 = bml::tuple<int&&>(bml::move(i1));
			auto t2 = bml::tuple<int&&>(bml::move(i2));
			
			auto&& ref = (t2 = bml::move(t1));
			
			return t2.get<0>()== 42 && &ref == &t2;
		}(42, 24));
	}
	
	// Check that the move assignment operator for an element does not participate in overload
	// resolution if that element is not move-assignable, and that the containing tuple is still
	// move-assignable if all elements are copy or move assignable.
	{
		// tuple is still "move-assignable" since non-move-assignable elements are still copy-
		// assignable - overload resolution selects the copy assignment operator for those elements.
        static_assert(bml::is_move_assignable_v<bml::tuple<copyable_no_move_assign>>);
		static_assert(bml::is_move_assignable_v<bml::tuple<copyable_no_move_assign,
			copyable_no_move_assign>>);
		static_assert(bml::is_move_assignable_v<bml::tuple<copyable_no_move_assign, int,
			move_assign>>);
        
        // Not move-assignable since at least one element is both not move-assignable and not copy-
		// assignable.
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const volatile&>>);
		static_assert(!bml::is_copy_assignable_v<bml::tuple<int const&&>>);
        static_assert(!bml::is_move_assignable_v<bml::tuple<no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::tuple<implicit_no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::tuple<triv_move_assign const>>);
		
		static_assert(!bml::is_move_assignable_v<bml::tuple<int, copyable_no_move_assign,
			int const>>);
		static_assert(!bml::is_move_assignable_v<bml::tuple<int, copyable_no_move_assign,
			int const volatile&>>);
		static_assert(!bml::is_move_assignable_v<bml::tuple<int, copyable_no_move_assign,
			int const&&>>);
		static_assert(!bml::is_move_assignable_v<bml::tuple<int, copyable_no_move_assign,
			no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::tuple<int, move_assign,
			implicit_no_move_assign>>);
        static_assert(!bml::is_move_assignable_v<bml::tuple<int, char, move_assign,
			triv_move_assign const>>);
	}
	
	// Check that tuple is trivially move-assignable if all elements are trivially move or copy
	// assignable.
	{
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int volatile>>);
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int&>>);
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int volatile&&>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::tuple<triv_move_assign>>);
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<triv_copy_assign>>);
		
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int, int, char, int&>>);
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int, triv_move_assign,
			triv_copy_assign, int volatile&&>>);
        static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int volatile, triv_move_assign,
			triv_move_assign, int&>>);
		static_assert(bml::is_trivially_move_assignable_v<bml::tuple<int volatile, triv_copy_assign,
			triv_copy_assign>>);
        
        static_assert(!bml::is_trivially_move_assignable_v<bml::tuple<move_assign>>);
		static_assert(!bml::is_trivially_move_assignable_v<bml::tuple<move_assign,
			triv_move_assign>>);
		static_assert(!bml::is_trivially_move_assignable_v<bml::tuple<move_assign,
			triv_move_assign, int, int>>);
	}
	
	// Check that all elements' destructors are invoked when the containing tuple is destroyed.
	{
        dtor<0>::count = 0;
        {
            auto t = bml::tuple<dtor<0>>();
        }
        bmltb_assert(dtor<0>::count == 1);
		
		dtor<0>::count = 0;
		dtor<1>::count = 0;
        {
            auto t = bml::tuple<dtor<0>, dtor<0>, dtor<1>, int>();
        }
        bmltb_assert(dtor<0>::count == 2);
		bmltb_assert(dtor<1>::count == 1);
	}
	
	// Check that tuple is not destructible if at least one element is not destructible.
	{
		static_assert(!bml::is_destructible_v<bml::tuple<no_dtor>>);
        static_assert(!bml::is_destructible_v<bml::tuple<no_dtor const volatile>>);
		
		static_assert(!bml::is_destructible_v<bml::tuple<int, dtor<0>, no_dtor,
			no_dtor>>);
        static_assert(!bml::is_destructible_v<bml::tuple<int, dtor<0>, no_dtor,
			no_dtor const volatile>>);
	}
	
	// Check that tuple is trivially destructible if all elements are trivially destructible.
	{
		static_assert(bml::is_trivially_destructible_v<bml::tuple<int>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<int const volatile>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<triv_dtor>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<triv_dtor const volatile>>);
		
		static_assert(bml::is_trivially_destructible_v<bml::tuple<int, triv_dtor,
			int>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<int, triv_dtor,
			int const volatile>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<int, triv_dtor,
			triv_dtor>>);
        static_assert(bml::is_trivially_destructible_v<bml::tuple<int, triv_dtor,
			triv_dtor const volatile>>);
        
        static_assert(!bml::is_trivially_destructible_v<bml::tuple<dtor<0>>>);
		static_assert(!bml::is_trivially_destructible_v<bml::tuple<int, dtor<0>, triv_dtor>>);
	}
	
	// Check that tuple_element names the I-th element in the tuple, with the tuple's cv-qualifiers
	// applied to that element.
    {
        check_tuple_element<0, bml::tuple<int>, int>();
		check_tuple_element<0, bml::tuple<int&&>, int&&>();
		check_tuple_element<0, bml::tuple<int const volatile&>, int const volatile&>();
        
        check_tuple_element<0, bml::tuple<int, double const volatile>, int>();
        check_tuple_element<1, bml::tuple<int, double const volatile>, double const volatile>();
		check_tuple_element<1, bml::tuple<int, double const&>, double const&>();
        
        check_tuple_element<0, bml::tuple<int const**, double&, multiply const>, int const**>();
        check_tuple_element<1, bml::tuple<int const**, double&, multiply const>, double&>();
        check_tuple_element<2, bml::tuple<int const**, double&, multiply const>, multiply const>();
    }
	
	// Check that tuple_size yields the number of elements in the tuple.
    {
        check_tuple_size<bml::tuple<int>, 1>();
        check_tuple_size<bml::tuple<int, double const>, 2>();
        check_tuple_size<bml::tuple<int const volatile, double const, no_dtor>, 3>();
    }
	
	// Check that member get returns a reference to the I-th element that is of the appropriate type
	// for the tuple's value category (i.e. lvalue reference if the tuple is an lvalue, rvalue
	// reference otherwise), with the tuple's const qualification applied to that element.
	{
		// Check return type.
        check_member_get_type<bml::tuple<int>, 0, int>();
        check_member_get_type<bml::tuple<int, double const>, 1, double const>();
        check_member_get_type<bml::tuple<int, copy_ctor volatile>, 1, copy_ctor volatile>();
        check_member_get_type<bml::tuple<int, copy_ctor, double const*, int>, 2, double const*>();
		check_member_get_type<bml::tuple<int, copy_ctor, double const*, int>, 3, int>();
        check_member_get_type<bml::tuple<int**, copy_ctor, double const*>, 0, int**>();
		check_member_get_type<bml::tuple<int&, int const&, int const volatile&>, 0, int&>();
		check_member_get_type<bml::tuple<int&, int const&, int const volatile&>, 1, int const&>();
		check_member_get_type<bml::tuple<int&, int const&, int const volatile&>, 2,
			int const volatile&>();
		check_member_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 0, int&&>();
		check_member_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 1,
			int const&&>();
		check_member_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 2,
			int const volatile&&>();
		
        // Check that correct reference is returned.
        static_assert([]
        {
            auto t = bml::tuple<bool>(true);
            return t.get<0>();
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            return t.get<0>() == 42 && t.get<1>().value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            t.get<0>() = 500;
            
            return t.get<0>() == 500 && t.get<1>().value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            return t.get<0>() == 42 && t.get<1>().value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            t.get<1>().value = 500;
            
            return t.get<0>() == 42 && t.get<1>().value == 500;
        }());
		
		static_assert([]
        {
			auto i = 24;
            auto t = bml::tuple<int, int&>(42, i);
            t.get<1>() = 500;
            
            return t.get<0>() == 42 && t.get<1>() == 500 && i == 500;
        }());
		
		static_assert([](int&& i)
		{
			auto t = bml::tuple<int&&, int>(bml::move(i), 42);
			t.get<0>() = 500;
			
			return t.get<0>()== 500 && t.get<1>()== 42 && i == 500;
		}(24));
	}
	
	// Check that non-member get returns a reference to the I-th element that is of the appropriate
	// type for the tuple's value category (i.e. lvalue reference if the tuple is an lvalue, rvalue
	// reference otherwise), with the tuple's const qualification applied to that element.
    {
        // Check return type.
        check_free_get_type<bml::tuple<int>, 0, int>();
        check_free_get_type<bml::tuple<int, double const>, 1, double const>();
        check_free_get_type<bml::tuple<int, copy_ctor volatile>, 1, copy_ctor volatile>();
        check_free_get_type<bml::tuple<int, copy_ctor, double const*>, 2, double const*>();
        check_free_get_type<bml::tuple<int**, copy_ctor, double const*>, 0, int**>();
		check_free_get_type<bml::tuple<int&, int const&, int const volatile&>, 0, int&>();
		check_free_get_type<bml::tuple<int&, int const&, int const volatile&>, 1, int const&>();
		check_free_get_type<bml::tuple<int&, int const&, int const volatile&>, 2,
			int const volatile&>();
		check_free_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 0, int&&>();
		check_free_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 1, int const&&>();
		check_free_get_type<bml::tuple<int&&, int const&&, int const volatile&&>, 2,
			int const volatile&&>();
        
        // Check that correct reference is returned.
        static_assert([]
        {
            auto t = bml::tuple<bool>(true);
            return bml::get<0>(t);
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            return bml::get<0>(t) == 42 && bml::get<1>(t).value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            bml::get<0>(t) = 500;
            
            return bml::get<0>(t) == 500 && bml::get<1>(t).value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            return bml::get<0>(t) == 42 && bml::get<1>(t).value == 54;
        }());
        
        static_assert([]
        {
            auto t = bml::tuple<int, multiply>(42, multiply(6, 9));
            bml::get<1>(t).value = 500;
            
            return bml::get<0>(t) == 42 && bml::get<1>(t).value == 500;
        }());
		
		static_assert([]
        {
			auto i = 24;
            auto t = bml::tuple<int, int&>(42, i);
            t.get<1>() = 500;
            
            return bml::get<0>(t) == 42 && bml::get<1>(t) == 500 && i == 500;
        }());
		
		static_assert([](int&& i)
		{
			auto t = bml::tuple<int&&, int>(bml::move(i), 42);
			t.get<0>() = 500;
			
			return bml::get<0>(t)== 500 && bml::get<1>(t)== 42 && i == 500;
		}(24));
    }
	
	// Check that member swap swaps all tuple elements with the argument tuple's elements.
	{
		// Non-constexpr context
		{
			auto c1 = 'a';
			auto c2 = 'x';
			auto t1 = bml::tuple<int, char&, multiply>(500, c1, multiply(6, 7));
			auto t2 = bml::tuple<int, char&, multiply>(42, c2, multiply(60, 70));
			
			t1.swap(t2);
			c1 = 'b';
			c2 = 'y';
			
            bmltb_assert(t1.get<0>() == 42);
			bmltb_assert(t1.get<1>() == 'y');
			bmltb_assert(t1.get<2>().value == 4200);
            bmltb_assert(t2.get<0>() == 500);
            bmltb_assert(t2.get<1>() == 'b');
			bmltb_assert(t2.get<2>().value == 42);
		}
		
		// Constexpr context
		static_assert([]()
		{
			auto t1 = bml::tuple<int, char, multiply>(500, 'x', multiply(6, 7));
			auto t2 = bml::tuple<int, char, multiply>(42, 'a', multiply(60, 70));
			
			t1.swap(t2);
			
            return t1.get<0>() == 42
				&& t1.get<1>() == 'a'
				&& t1.get<2>().value == 4200
				&& t2.get<0>() == 500
				&& t2.get<1>() == 'x'
				&& t2.get<2>().value == 42;
		}());
		
		// Check that the user-defined swap is called if it's available.
		{
            swappee::swap_called = false;
            auto t1 = bml::tuple<int, swappee>(100, 42);
            auto t2 = bml::tuple<int, swappee>(500, 24);
            
            t1.swap(t2);
            
            bmltb_assert(swappee::swap_called);
            bmltb_assert(t1.get<0>() == 500);
            bmltb_assert(t1.get<1>().value == 24);
			bmltb_assert(t2.get<0>() == 100);
            bmltb_assert(t2.get<1>().value == 42);
        }
	}
	
	// Check that member swap is not callable if any element is not swappable.
    {
        static_assert(!can_call_mem_swap<bml::tuple<not_swappable>>());
        static_assert(!can_call_mem_swap<bml::tuple<int, not_swappable, double>>());
    }
	
	// Check that free swap swaps the all tuple elements with the argument tuple's elements.
	{
		// Non-constexpr context
		{
			auto c1 = 'a';
			auto c2 = 'x';
			auto t1 = bml::tuple<int, char&, multiply>(500, c1, multiply(6, 7));
			auto t2 = bml::tuple<int, char&, multiply>(42, c2, multiply(60, 70));
			
			using bml::swap;
            using ::swap;
			swap(t1, t2);
			c1 = 'b';
			c2 = 'y';
			
            bmltb_assert(t1.get<0>() == 42);
			bmltb_assert(t1.get<1>() == 'y');
			bmltb_assert(t1.get<2>().value == 4200);
            bmltb_assert(t2.get<0>() == 500);
            bmltb_assert(t2.get<1>() == 'b');
			bmltb_assert(t2.get<2>().value == 42);
		}
		
		// Constexpr context
		static_assert([]()
		{
			auto t1 = bml::tuple<int, char, multiply>(500, 'x', multiply(6, 7));
			auto t2 = bml::tuple<int, char, multiply>(42, 'a', multiply(60, 70));
			
			using bml::swap;
            using ::swap;
			swap(t1, t2);
			
            return t1.get<0>() == 42
				&& t1.get<1>() == 'a'
				&& t1.get<2>().value == 4200
				&& t2.get<0>() == 500
				&& t2.get<1>() == 'x'
				&& t2.get<2>().value == 42;
		}());
		
		// Check that the user-defined swap is called if it's available.
		{
            swappee::swap_called = false;
            auto t1 = bml::tuple<int, swappee>(100, 42);
            auto t2 = bml::tuple<int, swappee>(500, 24);
            
            using bml::swap;
            using ::swap;
			swap(t1, t2);
            
            bmltb_assert(swappee::swap_called);
            bmltb_assert(t1.get<0>() == 500);
            bmltb_assert(t1.get<1>().value == 24);
			bmltb_assert(t2.get<0>() == 100);
            bmltb_assert(t2.get<1>().value == 42);
        }
	}
	
	// Check that free swap is not callable if any element is not swappable, and the tuple itself is
	// not move-constructible or move-assignable (so that the "generic" swap cannot be used).
	{
		static_assert(!bml::is_swappable_v<bml::tuple<int const&&>>);
		static_assert(!bml::is_swappable_v<bml::tuple<no_move_ctor>>);
		static_assert(!bml::is_swappable_v<bml::tuple<no_move_assign>>);
        static_assert(!bml::is_swappable_v<bml::tuple<not_swappable, no_move_assign>>);
        static_assert(!bml::is_swappable_v<bml::tuple<int, not_swappable, no_move_assign>>);
        static_assert(!bml::is_swappable_v<bml::tuple<int, no_move_ctor, double>>);
		static_assert(!bml::is_swappable_v<bml::tuple<int, no_move_ctor, double, int const&>>);
	}
	
	// Check that class template argument deduction deduces the correct element types.
	{
		auto c = 'a';
		auto& c_ref = c;
		auto const volatile& c_cvref = c;
		
		int int_arr[2] = {1, 2};
		int const c_int_arr[2] = {1, 2};
		
		auto mul = multiply(5, 9);
		auto copy = copy_ctor(42);
		auto mov = move_ctor(42);
		
		static_assert(bml::is_same_v<decltype(bml::tuple('a', 42, 10.4f)),
			bml::tuple<char, int, float>>);
		static_assert(bml::is_same_v<decltype(bml::tuple(c, c_ref, c_cvref)),
			bml::tuple<char, char, char>>);
		static_assert(bml::is_same_v<decltype(bml::tuple(int_arr, c_int_arr)),
			bml::tuple<int*, int const*>>);
		static_assert(bml::is_same_v<decltype(bml::tuple(mul, copy, bml::move(mov))),
			bml::tuple<multiply, copy_ctor, move_ctor>>);
	}
	
	// Check that tuple makes use of empty base optimization where possible.
	{
		static_assert(sizeof(bml::tuple<>) == 1);
		static_assert(sizeof(bml::tuple<empty>) == 1);
		static_assert(sizeof(bml::tuple<int, empty>) == sizeof(int));
		static_assert(sizeof(bml::tuple<int, empty, multiply>) == sizeof(int) + sizeof(multiply));
	}
	
    return 0;
}
