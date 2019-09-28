# `<bml/type_traits/remove_cvref.hpp>`
#### Table of Contents
- [`remove_cvref`](#remove_cvref)

## `remove_cvref`
```c++
template <typename T>
struct remove_cvref;

template <typename T>
using remove_cvref_ty = typename remove_cvref<T>::type;
```
Obtains the type being referred to by `T`, with top-level cv-qualifiers removed, if `T` is a
reference type. Otherwise, removes any top-level cv-qualifiers from `T`.

This provides a member type alias type which names:

- `V` if `T` is a reference to `U`, and `U` of the form `V const`, `V volatile` or
  `V const volatile`.
- `U` if `T` is of the form `U const`, `U volatile` or `U const volatile`.
- `T` otherwise.

Both `remove_cvref` and `remove_cvref_ty` are similar to `std::remove_cvref` and
`std::remove_cvref_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names:

- `U` with any top-level cv-qualifiers removed, if `T` is a reference to `U`.
- `T` with any top-level cv-qualifiers removed otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
