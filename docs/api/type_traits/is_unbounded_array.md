# `<bml/type_traits/is_unbounded_array.hpp>`
#### Table of Contents
- [`is_unbounded_array`](#is_unbounded_array)

## `is_unbounded_array`
```c++
template <typename T>
struct is_unbounded_array;

template <typename T>
constexpr auto is_unbounded_array_v = bool(is_unbounded_array<T>::value);
```
Checks if `T` is an array of unknown bound. This has a base characteristic of `bml::true_type` if
`T` is an array of unknown bound, and `bml::false_type` otherwise.

Both `is_unbounded_array` and `is_unbounded_array_v` are similar to `std::is_unbounded_array` and
`std::is_unbounded_array_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is an array of unknown bound.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
