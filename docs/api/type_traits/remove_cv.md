# `<bml/type_traits/remove_cv.hpp>`
#### Table of Contents
- [`remove_cv`](#remove_cv)

## `remove_cv`
```c++
template <typename T>
struct remove_cv;

template <typename T>
using remove_cv_ty = typename remove_cv<T>::type;
```
Removes any top-level cv-qualifiers from `T`. This provides a member type alias `type` which names:

- `U` if `T` is of the form `U const`, `U volatile` or `U const volatile`.
- `T` otherwise.

Both `remove_cv` and `remove_cv_ty` are similar to `std::remove_cv` and `std::remove_cv_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T` with any top-level cv-qualifiers removed.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
