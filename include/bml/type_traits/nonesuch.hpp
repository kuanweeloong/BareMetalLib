//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
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
