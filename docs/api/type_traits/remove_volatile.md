# `<bml/type_traits/remove_volatile.hpp>`
#### Table of Contents
- [`remove_volatile`](#remove_volatile)

## `remove_volatile`
```c++
template <typename T>
struct remove_volatile;

template <typename T>
using remove_volatile_ty = typename remove_volatile<T>::type;
```
Removes any top-level volatile qualifiers from `T`. This provides a member type alias `type `which
names `U` if `T` is of the form `U volatile`, and `T` otherwise.

Both `remove_volatile` and `remove_volatile_ty` are similar to `std::remove_volatile` and
`std::remove_volatile_t`, respectively, except that the latter has been suffixed with `_ty` for
POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T` with any top-level volatile qualifiers removed.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
