# `<bml/type_traits/is_union.hpp>`
#### Table of Contents
- [`is_union`](#is_union)

## `is_union`
```c++
template <typename T>
struct is_union;

template <typename T>
constexpr auto is_union_v = bool(is_union<T>::value);
```
Checks if `T` is a union type. This has a base characteristic of `bml::true_type` if `T` is a union
type, and `bml::false_type` otherwise.

Both `is_union` and `is_union_v` are similar to `std::is_union` and `std::is_union_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a union type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
