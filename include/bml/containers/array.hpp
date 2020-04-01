//
// Copyright (c) 2020 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once
#include <stddef.h>
#include "../type_traits/enable_if.hpp"
#include "../type_traits/integral_constant.hpp"
#include "../type_traits/is_const.hpp"
#include "../type_traits/is_same.hpp"
#include "../type_traits/is_swappable.hpp"
#include "../type_traits/pack_size.hpp"
#include "../utilities/move.hpp"
#include "../utilities/swap_ranges.hpp"
#include "tuple.hpp"

namespace bml
{
    template <typename T, ::ptrdiff_t Len>
    struct array
    {
        static_assert(Len >= 0, "Cannot have array of negative length.");

        // This can't be private as array needs to be an aggregate type.
        T m_elems[Len];

        [[nodiscard]] constexpr auto operator[](::ptrdiff_t n) & noexcept -> T&
        {
            return m_elems[n];
        }

        [[nodiscard]] constexpr auto operator[](::ptrdiff_t n) const& noexcept -> T const&
        {
            return m_elems[n];
        }

        [[nodiscard]] constexpr auto operator[](::ptrdiff_t n) && noexcept -> T&&
        {
            return bml::move(m_elems[n]);
        }

        [[nodiscard]] constexpr auto operator[](::ptrdiff_t n) const&& noexcept -> T const&&
        {
            return bml::move(m_elems[n]);
        }

        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() & noexcept -> T&
        {
            static_assert(0 <= I && I < Len, "get's index is out of bounds. (bml::array)");

            return (*this)[I];
        }

        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const& noexcept -> T const&
        {
            static_assert(0 <= I && I < Len, "get's index is out of bounds. (bml::array)");

            return (*this)[I];
        }

        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() && noexcept -> T&&
        {
            static_assert(0 <= I && I < Len, "get's index is out of bounds. (bml::array)");

            return bml::move(*this)[I];
        }

        template <::ptrdiff_t I>
        [[nodiscard]] constexpr auto get() const&& noexcept -> T const&&
        {
            static_assert(0 <= I && I < Len, "get's index is out of bounds. (bml::array)");

            return bml::move(*this)[I];
        }

        [[nodiscard]] constexpr auto front() & noexcept -> T&
        {
            return (*this)[0];
        }

        [[nodiscard]] constexpr auto front() const & noexcept -> T const&
        {
            return (*this)[0];
        }

        [[nodiscard]] constexpr auto front() && noexcept -> T&&
        {
            return bml::move(*this)[0];
        }

        [[nodiscard]] constexpr auto front() const && noexcept -> T const&&
        {
            return bml::move(*this)[0];
        }

        [[nodiscard]] constexpr auto back() & noexcept -> T&
        {
            return (*this)[Len - 1];
        }

        [[nodiscard]] constexpr auto back() const & noexcept -> T const&
        {
            return (*this)[Len - 1];
        }

        [[nodiscard]] constexpr auto back() && noexcept -> T&&
        {
            return bml::move(*this)[Len - 1];
        }

        [[nodiscard]] constexpr auto back() const && noexcept -> T const&&
        {
            return bml::move(*this)[Len - 1];
        }

        [[nodiscard]] constexpr auto data() noexcept -> T*
        {
            return m_elems;
        }

        [[nodiscard]] constexpr auto data() const noexcept -> T const*
        {
            return m_elems;
        }

        [[nodiscard]] constexpr auto empty() const noexcept -> bool
        {
            return false;
        }

        [[nodiscard]] constexpr auto size() const noexcept -> ::ptrdiff_t
        {
            return Len;
        }

        [[nodiscard]] constexpr auto max_size() const noexcept -> ::ptrdiff_t
        {
            return Len;
        }

        constexpr auto fill(T const& val) noexcept -> void
        {
            for (auto i = 0; i < Len; ++i)
            {
                (*this)[i] = val;
            }
        }
        template <bool AlwaysTrue = true, typename = enable_if_ty<AlwaysTrue && is_swappable_v<T>>>
        constexpr auto swap(array& a) noexcept -> void
        {
            bml::swap_ranges(m_elems, m_elems + Len, a.m_elems);
        }
    };

    template <typename T>
    struct array<T, 0>
    {
        [[nodiscard]] constexpr auto empty() const noexcept -> bool
        {
            return true;
        }

        [[nodiscard]] constexpr auto size() const noexcept -> ::ptrdiff_t
        {
            return 0;
        }

        [[nodiscard]] constexpr auto max_size() const noexcept -> ::ptrdiff_t
        {
            return 0;
        }

        template <bool AlwaysTrue = true, typename = enable_if_ty<AlwaysTrue && is_swappable_v<T>>>
        constexpr auto swap(array&) noexcept -> void {}

        // Member functions for reading/writing to the array are intentionally missing from this
        // specialization - there is no data to access!
    };

    template <typename T, typename... Args, typename = enable_if_ty<(is_same_v<T, Args> && ...)>>
    array(T, Args...) -> array<T, pack_size_v<Args...> + 1>;

    template <::ptrdiff_t I, typename T, ::ptrdiff_t Len>
    constexpr auto get(array<T, Len>& a) noexcept -> T&
    {
        return a.template get<I>();
    }

    template <::ptrdiff_t I, typename T, ::ptrdiff_t Len>
    constexpr auto get(array<T, Len> const& a) noexcept -> T const&
    {
        return a.template get<I>();
    }

    template <::ptrdiff_t I, typename T, ::ptrdiff_t Len>
    constexpr auto get(array<T, Len>&& a) noexcept -> T&&
    {
        return bml::move(a).template get<I>();
    }

    template <::ptrdiff_t I, typename T, ::ptrdiff_t Len>
    constexpr auto get(array<T, Len>const&& a) noexcept -> T const&&
    {
        return bml::move(a).template get<I>();
    }

    template <typename T, ::ptrdiff_t Len>
    constexpr auto swap(array<T, Len>& lhs, array<T, Len>& rhs) noexcept
        -> enable_if_ty<Len == 0 || is_swappable_v<T>>
    {
        lhs.swap(rhs);
    }

    template <typename T, ::ptrdiff_t Len>
    struct tuple_size<array<T, Len>> : integral_constant<::ptrdiff_t, Len> {};

    template <::ptrdiff_t I, typename T, ::ptrdiff_t Len>
    struct tuple_element<I, array<T, Len>>
    {
        static_assert(0 <= I && I < Len, "tuple_element's index is out of bounds. (bml::array)");

        using type = T;
    };
}
