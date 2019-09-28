# `<bml/type_traits/remove_pointer.hpp>`
#### Table of Contents
- [`remove_pointer`](#remove_pointer)

## `remove_pointer`
```c++
template <typename T>
struct remove_pointer;

template <typename T>
using remove_pointer_ty = typename remove_pointer<T>::type;
```
Obtains the type being pointed to by `T` if `T` is a pointer type. This provides a member type alias
`type` which names `U` if `T` is a pointer to `U`, and `T` otherwise.

Both `remove_pointer` and `remove_pointer_ty` are similar to `std::remove_pointer` and
`std::remove_pointer_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `U` if `T` is a pointer to `U`, and `T` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
