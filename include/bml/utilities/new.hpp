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

//
// Placement new declaration.
//
// A definition is not provided to prevent invoking UB - the Standard does not allow placement new
// to be replaced, and there is no guarantee that BML will compiled without the C++ standard
// library. This declaration also uses size_t instead of ptrdiff_t (unlike the rest of BML code) as
// this is required by the Standard.
//
[[nodiscard]] auto operator new(::size_t size, void* ptr) noexcept -> void*;
