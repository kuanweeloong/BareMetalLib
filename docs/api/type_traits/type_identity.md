# `<bml/type_traits/type_identity.hpp>`
#### Table of Contents
- [`type_identity`](#type_identity)

## `type_identity`
```c++
template <typename T>
struct type_identity;

template <typename T>
using type_identity_ty = typename type_identity<T>::type;
```
Yields `T` unchanged. This provides a member type alias `type` which names `T`.

Both `type_identity` and `type_identity_ty` are similar to `std::type_identity` and
`std::type_identity_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
