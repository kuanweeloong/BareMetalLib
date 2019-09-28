# `<bml/type_traits/remove_extent.hpp>`
#### Table of Contents
- [`remove_extent`](#remove_extent)

## `remove_extent`
```c++
template <typename T>
struct remove_extent;

template <typename T>
using remove_extent_ty = typename remove_extent<T>::type;
```
Removes the first array dimension from `T` if `T` is an array type. This provides a member type
alias `type` which names `U` if `T` is a an array of `U`, and `T `otherwise. If `T` is a
multi-dimensional array, only the first dimension is removed.

Both `remove_extent` and `remove_extent_ty` are similar to `std::remove_extent` and
`std::remove_extent_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `U` if `T` is an array of `U`, and `T `otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
