# `<bml/type_traits/bool_constant.hpp>`
#### Table of Contents
- [`bool_constant`](#bool_constant)

## `bool_constant`
```c++
template <bool B>
using bool_constant = bml::integral_constant<bool, B>;
```
An alias for `bml::integral_constant` with type `bool` and value `B`.

This is similar to `std::bool_constant`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
