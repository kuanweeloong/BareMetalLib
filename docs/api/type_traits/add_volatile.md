# `<bml/type_traits/add_volatile.hpp>`
#### Table of Contents
- [`add_volatile`](#add_volatile)

## `add_volatile`
```c++
template <typename T>
struct add_volatile;

template <typename T>
using add_volatile_ty = typename add_volatile<T>::type;
```
Adds a volatile qualifier to `T`. This provides a member type alias `type` which names `T volatile`.

Both `add_volatile` and `add_volatile_ty` are similar to `std::add_volatile` and
`std::add_volatile_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = T volatile;
```
Names a volatile qualified `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
