# `<bml/containers/in_place.hpp>`
#### Table of Contents
- [`in_place`](#in_place)

## `in_place`
```c++
struct in_place_ty;

constexpr auto in_place = in_place_ty();
```
A tag type for indicating that an action (e.g. construction) should be performed in-place.

Both `in_place` and `in_place_ty` are similar to `std::in_place` and `std::in_place_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
