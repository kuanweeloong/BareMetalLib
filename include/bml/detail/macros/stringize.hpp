//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

//
// Macro for stringizing stuff.
//
#define BML_STRINGIZE_1(...) #__VA_ARGS__
#define BML_STRINGIZE(...) BML_STRINGIZE_1(__VA_ARGS__)
