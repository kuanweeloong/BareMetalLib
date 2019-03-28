//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include <stddef.h>

//
// Placement new declarations.
//
// Definitions are not provided to prevent invoking UB - the Standard does not allow placement new
// to be replaced, and there is no guarantee that BML will compiled without the C++ standard
// library. This declaration also uses size_t instead of ptrdiff_t (unlike the rest of BML code) as
// this is required by the Standard.
//
[[nodiscard]] auto operator new(::size_t size, void* ptr) noexcept -> void*;
[[nodiscard]] auto operator new[](::size_t size, void* ptr) noexcept -> void*;
