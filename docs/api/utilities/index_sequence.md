# `<bml/utilities/index_sequence.hpp>`
#### Table of Contents
- [`index_sequence`](#index_sequence)

## `index_sequence`
```c++
template <ptrdiff_t... Is>
using index_sequence = bml::integer_sequence<ptrdiff_t, Is...>;
```
An alias for `bml::integer_sequence` with `ptrdiff_t` as the integer type.

This is similar to `std::index_sequence`, except that this uses `ptrdiff_t` as the integer type
instead of `size_t`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
