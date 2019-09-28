# `<bml/type_traits/remove_reference.hpp>`
#### Table of Contents
- [`remove_reference`](#remove_reference)

## `remove_reference`
```c++
template <typename T>
struct remove_reference;

template <typename T>
using remove_reference_ty = typename remove_reference<T>::type;
```
Obtains the type being referred to by `T` if `T` is a reference type. This provides a member type
alias `type` which names `U` if `T` is a reference to `U`, and `T` otherwise.

Both `remove_reference` and `remove_reference_ty` are similar to `std::remove_reference` and
`std::remove_reference_t`, respectively, except that the latter has been suffixed with `_ty` for
POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `U` if `T` is a reference to `U`, and `T` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
