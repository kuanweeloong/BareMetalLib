# `<bml/type_traits/detected_ty.hpp>`
#### Table of Contents
- [`detected_ty`](#detected_ty)

## `detected_ty`
```c++
template <template <typename...> typename Op, typename... Args>
using detected_ty = typename bml::detected_or<bml::nonesuch, Op, Args...>::type;
```
Yields `Op<Args...>` if it names a valid type, and `bml::nonesuch` otherwise. This is an alias for
`bml::detected_or`'s member type alias `type`, with `Default` set to `bml::nonesuch`.

This is similar to `std::experimental::detected_t` (as detailed in Library Fundamentals TSv3),
except that it has been suffixed with `_ty` for POSIX compatibility.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
