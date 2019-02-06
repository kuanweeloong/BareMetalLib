//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../basic_types/nullptr_ty.hpp"
#include "is_same.hpp"
#include "remove_cv.hpp"

namespace bml
{
    //
    // See std::is_null_pointer.
    //
    template <typename T>
    struct is_null_pointer : is_same<nullptr_ty, remove_cv_ty<T>> {};

    //
    // See std::is_null_pointer_v.
    //
    template <typename T>
    inline constexpr auto is_null_pointer_v = bool(is_null_pointer<T>::value);
}
