# `<bml/type_traits/add_cv.hpp>`
#### Table of Contents
- [`add_cv`](#add_cv)

## `add_cv`
```c++
template <typename T>
struct add_cv;

template <typename T>
using add_cv_ty = typename add_cv<T>::type;
```
Adds a const volatile qualifier to `T`. This provides a member type alias `type` which names
`T const volatile`.

Both `add_cv` and `add_cv_ty` are similar to `std::add_cv` and `std::add_cv_t`, respectively, except
that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = T const volatile;
```
Names a const volatile qualified `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
