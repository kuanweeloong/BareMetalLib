//
// Copyright (c) 2018 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once

namespace bml
{
    //
    // See std::nullptr_t, except that this is named nullptr_ty for POSIX compatibility.
    //
    using nullptr_ty = decltype(nullptr);
}
