# `<bml/type_traits/is_same.hpp>`
#### Table of Contents
- [`is_same`](#is_same)

## `is_same`
```c++
template <typename T, typename U>
struct is_same;

template <typename T, typename U>
constexpr auto is_same_v = bool(is_same<T, U>::value);
```
Checks if `T` names the same type as `U`. This has a base characteristic of `bml::true_type` if `T`
names the same type as `U`, and `bml::false_type` otherwise.

Both `is_same` and `is_same_v` are similar to `std::is_same` and `std::is_same_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` names the same type as `U`.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
