# `<bml/basic_types/nullptr_ty.hpp>`
#### Table of Contents
- [`nullptr_ty`](#nullptr_ty)

## `nullptr_ty`
```c++
using nullptr_ty = decltype(nullptr);
```
Represents the type of the null pointer literal, `nullptr`.

This is similar to `std::nullptr_t`, except that it has been suffixed with `_ty` for POSIX
compatibility.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
