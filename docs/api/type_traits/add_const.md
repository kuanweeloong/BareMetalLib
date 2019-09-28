# `<bml/type_traits/add_const.hpp>`
#### Table of Contents
- [`add_const`](#add_const)

## `add_const`
```c++
template <typename T>
struct add_const;

template <typename T>
using add_const_ty = typename add_const<T>::type;
```
Adds a const qualifier to `T`. This provides a member type alias `type` which names `T const`.

Both `add_const` and `add_const_ty` are similar to `std::add_const` and `std::add_const_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = T const;
```
Names a const qualified `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
