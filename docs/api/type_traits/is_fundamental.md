# `<bml/type_traits/is_fundamental.hpp>`
#### Table of Contents
- [`is_fundamental`](#is_fundamental)

## `is_fundamental`
```c++
template <typename T>
struct is_fundamental;

template <typename T>
constexpr auto is_fundamental_v = bool(is_fundamental<T>::value);
```
Checks if `T` is a fundamental type (i.e. arithmetic type, possibly cv-qualified `void` or possibly
cv-qualified `bml::nullptr_ty`). This has a base characteristic of `bml::true_type` if `T` is a
fundamental type, and `bml::false_type` otherwise.

Both `is_fundamental` and `is_fundamental_v` are similar to `std::is_fundamental` and
`std::is_fundamental_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a fundamental type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
