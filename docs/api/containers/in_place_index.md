# `<bml/containers/in_place_index.hpp>`
#### Table of Contents
- [`in_place_index`](#in_place_index)

## `in_place_index`
```c++
template <ptrdiff_t I> 
struct in_place_index_ty;

template <ptrdiff_t I>
constexpr auto in_place_index = in_place_index_ty<I>();
```
A tag type for indicating that an action (e.g. construction) on something associated with an index
`I` (e.g. index of a type in a template parameter pack) should be performed in-place.

Both `in_place_index` and `in_place_index_ty` are similar to `std::in_place_index` and
`std::in_place_index_t`, respectively, except that they use `ptrdiff_t` for the index instead of
`size_t`, and that the latter has been suffixed with `_ty` for POSIX compatibility.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
