//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "in_place.hpp"
#include "../type_traits/enable_if.hpp"
#include "../type_traits/pack_size.hpp"
#include "../type_traits/type_pack_element.hpp"
#include "../type_traits/conjunction.hpp"
#include "../type_traits/true_type.hpp"
#include "../type_traits/bool_constant.hpp"
#include "../type_traits/add_const.hpp"
#include "../type_traits/add_volatile.hpp"
#include "../type_traits/add_cv.hpp"
#include "../type_traits/remove_reference.hpp"
#include "../type_traits/remove_cvref.hpp"
#include "../type_traits/is_const.hpp"
#include "../type_traits/is_same.hpp"
#include "../type_traits/is_empty.hpp"
#include "../type_traits/is_final.hpp"
#include "../type_traits/is_lvalue_reference.hpp"
#include "../type_traits/is_rvalue_reference.hpp"
#include "../type_traits/is_list_convertible.hpp"
#include "../type_traits/is_default_constructible.hpp"
#include "../type_traits/is_copy_constructible.hpp"
#include "../type_traits/is_convertible.hpp"
#include "../type_traits/is_swappable.hpp"
#include "../utilities/addressof.hpp"
#include "../utilities/swap.hpp"
#include "../utilities/move.hpp"
#include "../utilities/forward.hpp"
#include "../utilities/index_sequence.hpp"
#include "../utilities/make_index_sequence.hpp"

namespace bml
{
    template <typename... Ts>
    class tuple;
    
    namespace detail::tuple_detail
    {
        // Helper to allow parameter pack expansion with function invocations.
        template <typename... Ts>
        constexpr auto swallow(Ts&&...) -> void {}
        
        // Helper to check if using Ts... as the sole universal reference argument in a tuple
        // constructor will cause a conflict with its move or copy constructors.
        template <typename Tuple, typename... Ts>
        struct no_special_ctor_conflict : true_type {};
        
        template <typename Tuple, typename T>
        struct no_special_ctor_conflict<Tuple, T>
            : bool_constant<!is_same_v<Tuple, remove_cvref_ty<T>>> {};
        
        // Helper to match the const qualification of type with another type.
        template <typename T, typename MatchWith>
        struct match_const { using type = T; };
        
        template <typename T, typename MatchWith>
        struct match_const<T, MatchWith const> { using type = T const; };
        
        template <typename T, typename MatchWith>
        using match_const_ty = typename match_const<T, MatchWith>::type;
        
        // Helper base class to implictly disable a copy constructor in the derived class.
        struct disable_copy_ctor
        {
            disable_copy_ctor(disable_copy_ctor const&) = delete;
            
            constexpr disable_copy_ctor() noexcept = default;
            constexpr disable_copy_ctor(disable_copy_ctor&&) noexcept = default;
            constexpr auto operator=(disable_copy_ctor const&) noexcept -> disable_copy_ctor&
                = default;
            constexpr auto operator=(disable_copy_ctor&&) noexcept -> disable_copy_ctor&
                = default;
        };
        
        // Helper function to determine the type of element storage to be instantiated.
        enum class leaf_type
        {
            lval_ref,
            rval_ref,
            ebo,
            normal
        };
        
        template <typename T>
        constexpr auto get_leaf_type() noexcept -> leaf_type
        {
            if constexpr (is_lvalue_reference_v<T>)
            {
                return leaf_type::lval_ref;
            }
            else if constexpr (is_rvalue_reference_v<T>)
            {
                return leaf_type::rval_ref;
            }
            else if constexpr (is_empty_v<T> && !is_final_v<T>)
            {
                return leaf_type::ebo;
            }
            else
            {
                return leaf_type::normal;
            }
        }
        
        // Helper to convert references to pointers. Conversion is done in a simllar way to that of
        // reference_wrapper, except that this also accepts rvalue references (i.e. conversion is
        // done as if by T&& t = std::forward<U>(x)).
        //
        // Note that despite the syntax, the argument t is not a forwarding reference - T should be
        // explicitly specified.
        template <typename T>
        constexpr auto ref_to_ptr(T&& t) noexcept -> remove_reference_ty<T>*
        {
            return bml::addressof(t);
        }
        
        // Stores a single element of a tuple.
        template <::ptrdiff_t Index, typename T, leaf_type = tuple_detail::get_leaf_type<T>()>
        struct leaf
        {
            T m_value;
            
            // Cannot be defaulted - the defaulted constructor is non-constexpr if T is not a class
            // type.
            constexpr leaf() noexcept : m_value() {}
            
            template <typename Value>
            constexpr leaf(in_place_ty, Value&& v) noexcept : m_value(bml::forward<Value>(v)) {}
            
            constexpr auto get() noexcept -> T&
            {
                return m_value;
            }
            
            constexpr auto get() const noexcept -> T const&
            {
                return m_value;
            }
            
            // This returns an int so that it can be used as an argument to swallow().
            constexpr auto swap(leaf& other) noexcept -> int
            {
                using bml::swap;
                swap(m_value, other.m_value);
                
                return 0;
            }
        };
        
        // Storage for references. Converts the reference to a pointer to allow for compiler-
        // generated copy/move constructors and copy/move assignments, some of which would otherwise
        // have been implicitly deleted. This allows the top-level tuple to maintain triviality of
        // the special member functions.
        template <::ptrdiff_t Index, typename T>
        struct leaf<Index, T, leaf_type::lval_ref>
        {
            using PointerType = match_const_ty<remove_reference_ty<T>*, remove_reference_ty<T>>;
            PointerType m_value;
            
            template <typename Value>
            constexpr leaf(in_place_ty, Value&& v) noexcept
                : m_value(tuple_detail::ref_to_ptr<T>(bml::forward<Value>(v))) {}
            
            constexpr auto get() noexcept -> T&
            {
                return *m_value;
            }
            
            constexpr auto get() const noexcept -> T const&
            {
                return *m_value;
            }
            
            // This returns an int so that it can be used as an argument to swallow().
            constexpr auto swap(leaf& other) noexcept -> int
            {
                using bml::swap;
                swap(m_value, other.m_value);
                
                return 0;
            }
        };
        
        template <::ptrdiff_t Index, typename T>
        struct leaf<Index, T, leaf_type::rval_ref> : disable_copy_ctor
        {
            // Note: rvalue references are not copy constructible, so this class inherits from
            // disable_copy_ctor.
            
            using PointerType = match_const_ty<remove_reference_ty<T>*, remove_reference_ty<T>>;
            PointerType m_value;
            
            template <typename Value>
            constexpr leaf(in_place_ty, Value&& v) noexcept
                : m_value(tuple_detail::ref_to_ptr<T>(bml::forward<Value>(v))) {}
            
            constexpr auto get() noexcept -> T&
            {
                return *m_value;
            }
            
            constexpr auto get() const noexcept -> T const&
            {
                return *m_value;
            }
            
            // This returns an int so that it can be used as an argument to swallow().
            constexpr auto swap(leaf& other) noexcept -> int
            {
                using bml::swap;
                swap(m_value, other.m_value);
                
                return 0;
            }
        };
        
        // Storage for empty, non-final types which takes advantage of EBO.
        template <::ptrdiff_t Index, typename T>
        struct leaf<Index, T, leaf_type::ebo> : T
        {
            constexpr leaf() noexcept = default;
            
            template <typename Value>
            constexpr leaf(in_place_ty, Value&& v) noexcept : T(bml::forward<Value>(v)) {}
            
            constexpr auto get() noexcept -> T&
            {
                return static_cast<T&>(*this);
            }
            
            constexpr auto get() const noexcept -> T const&
            {
                return static_cast<T const&>(*this);
            }
            
            // This returns an int so that it can be used as an argument to swallow().
            constexpr auto swap(leaf& other) noexcept -> int
            {
                using bml::swap;
                swap(static_cast<T&>(*this), static_cast<T&>(other));
                
                return 0;
            }
        };
        
        // Tuple base class which associates an index with a stored element; this allows the top-
        // level tuple type to store multiple elements of the same type.
        template <typename... Ts>
        struct impl;
        
        template <::ptrdiff_t... Is, typename... Ts>
        struct impl<index_sequence<Is...>, Ts...> : leaf<Is, Ts>...
        {
            constexpr impl() noexcept = default;
            
            template <typename... Values>
            constexpr impl(in_place_ty, Values&&... vs) noexcept
                : leaf<Is, Ts>(in_place, bml::forward<Values>(vs))... {}
            
            template <::ptrdiff_t I>
            constexpr auto get() noexcept -> type_pack_element_ty<I, Ts...>&
            {
                using base = leaf<I, type_pack_element_ty<I, Ts...>>;
                return static_cast<base&>(*this).get();
            }
            
            template <::ptrdiff_t I>
            constexpr auto get() const noexcept -> type_pack_element_ty<I, Ts...> const&
            {
                using base = leaf<I, type_pack_element_ty<I, Ts...>>;
                return static_cast<base const&>(*this).get();
            }
            
            constexpr auto swap(impl& other) noexcept -> void
            {
                tuple_detail::swallow(static_cast<leaf<Is, Ts>&>(*this)
                    .swap(static_cast<leaf<Is, Ts>&>(other))...);
            }
        };
    }

    template <typename T>
    struct tuple_size;
    
    template <typename... Ts>
    struct tuple_size<tuple<Ts...>> : pack_size<Ts...> {};
    
    template <typename T>
    struct tuple_size<T const> : tuple_size<T> {};
    
    template <typename T>
    struct tuple_size<T volatile> : tuple_size<T> {};
    
    template <typename T>
    struct tuple_size<T const volatile> : tuple_size<T> {};

    template <typename T>
    inline constexpr auto tuple_size_v = ::ptrdiff_t(tuple_size<T>::value);

    template <::ptrdiff_t I, typename T>
    struct tuple_element;
    
    template <::ptrdiff_t I, typename... Ts>
    struct tuple_element<I, tuple<Ts...>>
    {
        static_assert(0 <= I && I < pack_size_v<Ts...>, "tuple index is out of bounds.");
        
        using type = type_pack_element_ty<I, Ts...>;
    };
    
    template <::ptrdiff_t I, typename T>
    struct tuple_element<I, T const> : add_const<typename tuple_element<I, T>::type> {};
    
    template <::ptrdiff_t I, typename T>
    struct tuple_element<I, T volatile> : add_volatile<typename tuple_element<I, T>::type> {};
    
    template <::ptrdiff_t I, typename T>
    struct tuple_element<I, T const volatile> : add_cv<typename tuple_element<I, T>::type> {};
    
    template <::ptrdiff_t I, typename T>
    using tuple_element_ty = typename tuple_element<I, T>::type;

    template <typename... Ts>
    class tuple : detail::tuple_detail::impl<make_index_sequence<pack_size_v<Ts...>>, Ts...>
    {
    private:
        
        using base = detail::tuple_detail::impl<make_index_sequence<pack_size_v<Ts...>>, Ts...>;
        
    public:

        template <bool AlwaysTrue = true, enable_if_ty<AlwaysTrue
            && conjunction_v<is_default_constructible<Ts>...>
            && conjunction_v<is_list_convertible<Ts>...>>* = nullptr>
        constexpr tuple() noexcept {}
        
        template <bool AlwaysTrue = true, enable_if_ty<AlwaysTrue
            && conjunction_v<is_default_constructible<Ts>...>
            && !conjunction_v<is_list_convertible<Ts>...>>* = nullptr>
        constexpr explicit tuple() noexcept {}

        template <typename... Values, enable_if_ty<
            detail::tuple_detail::no_special_ctor_conflict<tuple, Values...>::value
            && pack_size_v<Values...> == pack_size_v<Ts...>
            && conjunction_v<is_constructible<Ts, Values>...>
            && conjunction_v<is_convertible<Values, Ts>...>>* = nullptr>
        constexpr tuple(Values&&... vs) noexcept
            : base(in_place, bml::forward<Values>(vs)...) {}
        
        template <typename... Values, enable_if_ty<
            detail::tuple_detail::no_special_ctor_conflict<tuple, Values...>::value
            && pack_size_v<Values...> == pack_size_v<Ts...>
            && conjunction_v<is_constructible<Ts, Values>...>
            && !conjunction_v<is_convertible<Values, Ts>...>>* = nullptr>
        explicit constexpr tuple(Values&&... vs) noexcept
            : base(in_place, bml::forward<Values>(vs)...) {}

        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() & noexcept -> tuple_element_ty<I, tuple>&
        {
            return static_cast<base&>(*this).template get<I>();
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() && noexcept -> tuple_element_ty<I, tuple>&&
        {
            return bml::move(static_cast<base&>(*this).template get<I>());
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const & noexcept -> tuple_element_ty<I, tuple> const&
        {
            return static_cast<base const&>(*this).template get<I>();
        }
        
        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const && noexcept -> tuple_element_ty<I, tuple> const&&
        {
            return bml::move(static_cast<base const&>(*this).template get<I>());
        }

        template <bool AlwaysTrue = true, typename = enable_if_ty<AlwaysTrue
            && conjunction_v<is_swappable<Ts>...>>>
        constexpr auto swap(tuple& other) noexcept -> void
        {
            static_cast<base&>(*this).swap(other);
        }
    };
    
    template <>
    class tuple<>
    {
    public:
    
        constexpr tuple() noexcept = default;
        constexpr auto swap(tuple&) noexcept -> void {}
        
    };
    
    template <typename... Ts>
    tuple(Ts...) -> tuple<Ts...>;

    template <::ptrdiff_t I, typename... Ts>
    [[nodiscard]] constexpr auto get(tuple<Ts...>& t) noexcept
        -> tuple_element_ty<I, tuple<Ts...>>&
    {
        return t.template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    [[nodiscard]] constexpr auto get(tuple<Ts...> const& t) noexcept
        -> tuple_element_ty<I, tuple<Ts...>> const&
    {
        return t.template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    [[nodiscard]] constexpr auto get(tuple<Ts...>&& t) noexcept
        -> tuple_element_ty<I, tuple<Ts...>>&&
    {
        return bml::move(t).template get<I>();
    }
    
    template <::ptrdiff_t I, typename... Ts>
    [[nodiscard]] constexpr auto get(tuple<Ts...> const&& t) noexcept
        -> tuple_element_ty<I, tuple<Ts...>> const&&
    {
        return bml::move(t).template get<I>();
    }

    template <typename... Ts>
    constexpr auto swap(tuple<Ts...>& lhs, tuple<Ts...>& rhs) noexcept -> decltype(lhs.swap(rhs))
    {
        lhs.swap(rhs);
    }
}
