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

namespace bml
{
    //
    // See Library Fundamentals TS v3's std::experimental::nonesuch, except that this also
    // incorporates changes from Defect Report #2960 ("nonesuch is insufficiently useless").
    //
    struct nonesuch
    {
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        auto operator=(nonesuch const&) noexcept -> void = delete;
    };
}
