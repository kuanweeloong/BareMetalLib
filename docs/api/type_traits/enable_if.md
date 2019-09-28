# `<bml/type_traits/enable_if.hpp>`
#### Table of Contents
- [`enable_if`](#enable_if)

## `conditional`
```c++
template <bool B, typename T = void>
struct enable_if;

template <bool B, typename T = void>
using enable_if_ty = typename enable_if<B, T>::type;
```
Selectively yields `T` depending on the value of `B`. This provides a member type alias `type` which
names `T` if `B` is `true`; otherwise, this does not define any member `type`.

Both `enable_if` and `enable_if_ty` are similar to `std::enable_if` and `std::enable_if_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T` if `B` is `true`; otherwise, this alias is unavailable.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
