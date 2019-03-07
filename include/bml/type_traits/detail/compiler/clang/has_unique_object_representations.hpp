//
// Copyright (c) 2019 Wee Loong Kuan
//
// This file is licensed under the MIT license. For more details, see the LICENSE.md file in the
// top-level directory of this distribution.
//

#pragma once
#include "../../../bool_constant.hpp"
#include "../../../remove_cv.hpp"
#include "../../../remove_all_extents.hpp"

namespace bml::detail::has_unique_object_representations_detail
{
    template <typename T>
    struct impl :
        bool_constant<__has_unique_object_representations(remove_cv_ty<remove_all_extents_ty<T>>)>
    {};
}
