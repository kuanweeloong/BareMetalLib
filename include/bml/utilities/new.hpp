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
