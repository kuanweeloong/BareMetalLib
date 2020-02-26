//
// Copyright (c) 2019 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
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
    
    struct nullopt_ty
    {
        explicit constexpr nullopt_ty(detail::optional_detail::nullopt_tag) noexcept {}
    };
    
    inline constexpr auto nullopt = nullopt_ty(detail::optional_detail::nullopt_tag());
    
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

        constexpr optional()           noexcept : m_storage(in_place_index<0>) {}
        constexpr optional(nullopt_ty) noexcept : m_storage(in_place_index<0>) {}
        
        template <typename... Args, typename = enable_if_ty<is_constructible_v<T, Args&&...>>>
        constexpr explicit optional(in_place_ty, Args&&... args) noexcept
            : m_storage(in_place_index<1>, bml::forward<Args>(args)...) {}
        
        auto reset() noexcept -> void { m_storage.template emplace<0>(); } 
        auto operator=(nullopt_ty) noexcept -> optional& { reset(); return *this; }
        
        [[nodiscard]] constexpr auto has_value() const noexcept -> bool
        {
            return m_storage.index() != 0;
        }
        
        [[nodiscard]] constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }

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

        [[nodiscard]] constexpr auto operator->() noexcept -> T*
        {
            return bml::addressof(value());
        }
        
        [[nodiscard]] constexpr auto operator->() const noexcept -> T const*
        {
            return bml::addressof(value());
        }

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
        
        template <typename... Args, typename = enable_if_ty<is_constructible_v<T, Args...>>>
        auto emplace(Args&&... args) noexcept -> T&
        {
            return m_storage.template emplace<1>(bml::forward<Args>(args)...);
        }
    };

    template <typename T>
    inline auto swap(optional<T>& lhs, optional<T>& rhs) noexcept -> decltype(lhs.swap(rhs))
    {
        lhs.swap(rhs);
    }
}
