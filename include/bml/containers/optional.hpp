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

#pragma once
#include "../type_traits/enable_if.hpp"
#include "../type_traits/is_same.hpp"
#include "../type_traits/is_void.hpp"
#include "../type_traits/is_reference.hpp"
#include "../type_traits/is_array.hpp"
#include "../type_traits/is_constructible.hpp"
#include "../type_traits/is_swappable.hpp"
#include "../type_traits/is_move_constructible.hpp"
#include "../utilities/forward.hpp"
#include "../utilities/move.hpp"
#include "../utilities/addressof.hpp"
#include "variant.hpp"
#include "in_place.hpp"
#include "in_place_index.hpp"

namespace bml
{
    namespace detail::optional_detail
    {
        struct nullopt_tag {};
        struct no_value {};
    }
    
    //
    // See std::nullopt_t, except that this has been named nullopt_ty for POSIX compatibility.
    //
    struct nullopt_ty
    {
        explicit constexpr nullopt_ty(detail::optional_detail::nullopt_tag) noexcept {}
    };
    
    //
    // See std::nullopt.
    //
    inline constexpr auto nullopt = nullopt_ty(detail::optional_detail::nullopt_tag());
    
    //
    // An optional value type similar to std::optional.
    //
    // This differs from std::optional in that this does not support any member function overloads
    // which take in std::initializer_list (since BML does not assume that the C++ standard library
    // is available).
    //
    // There are also several features that are not yet supported, but in the pipeline to be done
    // soon (tm):
    // 
    // 1. value_or.
    // 2. Coverting constructors and assignment.
    // 3. Comparison operators.
    // 4. Deduction guide.
    //
    template <typename T>
    class optional
    {
        variant<detail::optional_detail::no_value, T> m_storage;
        
    public:
        
        static_assert(!is_same_v<remove_cvref_ty<T>, in_place_ty>,
            "optional cannot hold in_place_ty.");
        static_assert(!is_same_v<remove_cvref_ty<T>, nullopt_ty>,
            "optional cannot hold nullopt_ty.");
        
        static_assert(!is_void_v<T>, "optional cannot hold void.");
        static_assert(!is_array_v<T>, "optional cannot hold array types.");
        static_assert(!is_reference_v<T>, "optional cannot hold reference types.");
        
        using value_type = T;
    
        //
        // Constructs an optional that does not hold a value.
        //
        constexpr optional()           noexcept : m_storage(in_place_index<0>) {}
        constexpr optional(nullopt_ty) noexcept : m_storage(in_place_index<0>) {}
        
        //
        // Constructs an optional holding a value of type T via direct-non-list-initialization of T
        // with forward<Args>(args).... This does not participate in overload resolution unless T is
        // constructible from Args....
        //
        template <typename... Args, typename = enable_if_ty<is_constructible_v<T, Args&&...>>>
        constexpr explicit optional(in_place_ty, Args&&... args) noexcept
            : m_storage(in_place_index<1>, bml::forward<Args>(args)...) {}
        
        //
        // Destroys the currently held value, if any, and resets this optional to a state where it
        // does not hold a value.
        //
        auto reset() noexcept -> void { m_storage.template emplace<0>(); } 
        auto operator=(nullopt_ty) noexcept -> optional& { reset(); return *this; }
        
        //
        // Checks if this optional holds a value.
        //
        [[nodiscard]] constexpr auto has_value() const noexcept -> bool
        {
            return m_storage.index() != 0;
        }
        
        [[nodiscard]] constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }
        
        //
        // Accessors for currently held value. Their behavior is undefined if there is no currently
        // held value.
        //
        [[nodiscard]] constexpr auto value() & noexcept -> T&
        {
            return m_storage.template get<1>();
        }
        
        [[nodiscard]] constexpr auto value() const & noexcept -> T const&
        {
            return m_storage.template get<1>();
        }
        
        [[nodiscard]] constexpr auto value() && noexcept -> T&&
        {
            return bml::move(m_storage).template get<1>();
        }
        
        [[nodiscard]] constexpr auto value() const && noexcept -> T const&&
        {
            return bml::move(m_storage).template get<1>();
        }
        
        [[nodiscard]] constexpr auto operator*() & noexcept -> T&
        {
            return value();
        }
        
        [[nodiscard]] constexpr auto operator*() const & noexcept -> T const&
        {
            return value();
        }
        
        [[nodiscard]] constexpr auto operator*() && noexcept -> T&&
        {
            return bml::move(*this).value();
        }
        
        [[nodiscard]] constexpr auto operator*() const && noexcept -> T const&&
        {
            return bml::move(*this).value();
        }
        
        //
        // Returns a pointer to the currently held value.
        //
        [[nodiscard]] constexpr auto operator->() noexcept -> T*
        {
            return bml::addressof(value());
        }
        
        [[nodiscard]] constexpr auto operator->() const noexcept -> T const*
        {
            return bml::addressof(value());
        }
        
        //
        // Swaps the currently contained value with the value held by the argument optional. This
        // does not participate in overload resolution unless T is swappable and move-constructible.
        //
        template <bool AlwaysTrue = true, typename = enable_if_ty<AlwaysTrue
            && is_swappable_v<T> && is_move_constructible_v<T>>>
        auto swap(optional& other) noexcept -> void
        {
            // We call m_storage's swap only when both optionals have values to save two moves in
            // the other cases (variant's swap moves the argument into a temporary, which we don't
            // need to do when one optional does not hold a value).
            
            if (has_value() && other.has_value())
            {
                m_storage.swap(other.m_storage);
            }
            else if (has_value())
            {
                other.emplace(bml::move(value()));
                reset();
            }
            else if (other.has_value())
            {
                emplace(bml::move(other.value()));
                other.reset();
            }
        }
        
        //
        // Constructs a value of type T in this optional in-place. If there is a currently held
        // value, this destroys the current value before performing the in-place construction. This
        // does not participate in overload resolution if T is not constructible from Args....
        //
        template <typename... Args, typename = enable_if_ty<is_constructible_v<T, Args...>>>
        auto emplace(Args&&... args) noexcept -> T&
        {
            return m_storage.template emplace<1>(bml::forward<Args>(args)...);
        }
    };
    
    //
    // See std::swap for optionals.
    //
    template <typename T>
    inline auto swap(optional<T>& lhs, optional<T>& rhs) noexcept -> decltype(lhs.swap(rhs))
    {
        lhs.swap(rhs);
    }
}
