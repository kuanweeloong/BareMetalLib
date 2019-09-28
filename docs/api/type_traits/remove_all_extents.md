# `<bml/type_traits/remove_all_extents.hpp>`
#### Table of Contents
- [`remove_all_extents`](#remove_all_extents)

## `remove_all_extents`
```c++
template <typename T>
struct remove_all_extents;

template <typename T>
using remove_all_extents_ty = typename remove_all_extents<T>::type;
```
Removes all array dimensions from `T` if `T` is an array type. This provides a member type alias
`type` which names `U` if `T` is a multi-dimensional array of `U`, and `T `otherwise.

Both `remove_all_extents` and `remove_all_extents_ty` are similar to `std::remove_all_extents` and
`std::remove_all_extents_t`, respectively, except that the latter has been suffixed with `_ty` for
POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `U` if `T` is a multi-dimensional array of `U`, and `T `otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
