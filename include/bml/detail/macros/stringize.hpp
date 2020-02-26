//
// Copyright (c) 2018 Wee Loong Kuan
//
// Part of BareMetalLib, under the Apache License v2.0 with LLVM Exceptions. See
// https://llvm.org/LICENSE.txt for license information.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//

#pragma once

// Macro for stringizing stuff.
#define BML_STRINGIZE_1(...) #__VA_ARGS__
#define BML_STRINGIZE(...) BML_STRINGIZE_1(__VA_ARGS__)
