# `<bml/type_traits/remove_const.hpp>`
#### Table of Contents
- [`remove_const`](#remove_const)

## `remove_const`
```c++
template <typename T>
struct remove_const;

template <typename T>
using remove_const_ty = typename remove_const<T>::type;
```
Removes any top-level const qualifiers from `T`. This provides a member type alias `type` which
names `U` if `T` is of the form `U const`, and `T `otherwise.

Both `remove_const` and `remove_const_ty` are similar to `std::remove_const` and
`std::remove_const_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T` with any top-level const qualifiers removed.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
