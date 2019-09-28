# `<bml/type_traits/conditional.hpp>`
#### Table of Contents
- [`conditional`](#conditional)

## `conditional`
```c++
template <bool B, typename T, typename F>
struct conditional;

template <bool B, typename T, typename F>
using conditional_ty = typename conditional<B, T, F>::type;
```
Selects a type based on the value of `B`. This provides a member type alias `type` which names `T`
if `B` is `true`, and `F` otherwise.

Both `conditional` and `conditional_ty` are similar to `std::conditional` and `std::conditional_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `T` if `B` is `true`, and `F` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
