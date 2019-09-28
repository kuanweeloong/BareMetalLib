# `<bml/utilities/make_integer_sequence.hpp>`
#### Table of Contents
- [`make_integer_sequence`](#make_integer_sequence)

## `make_integer_sequence`
```c++
template <typename T, T N>
using make_integer_sequence = /* ... */;
```
Generates a `bml::integer_sequence` of `T`s containing integers `0` to `N - 1`. If `N` is `0`, this
names `bml::integer_sequence<T>`.

If `N` is negative, the program is ill-formed. 

This is similar to `std::make_integer_sequence`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
