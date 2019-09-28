# `<bml/type_traits/is_const.hpp>`
#### Table of Contents
- [`is_const`](#is_const)

## `is_const`
```c++
template <typename T>
struct is_const;

template <typename T>
constexpr auto is_const_v = bool(is_const<T>::value);
```
Checks if `T` has a top-level const qualifier. This has a base characteristic of `bml::true_type` if
`T` has a top-level const qualifier, and `bml::false_type` otherwise.

Both `is_const` and `is_const_v` are similar to `std::is_const` and `std::is_const_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` has a top-level const qualifier.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
