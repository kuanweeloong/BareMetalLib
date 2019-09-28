# `<bml/type_traits/is_volatile.hpp>`
#### Table of Contents
- [`is_volatile`](#is_volatile)

## `is_volatile`
```c++
template <typename T>
struct is_volatile;

template <typename T>
constexpr auto is_volatile_v = bool(is_volatile<T>::value);
```
Checks if `T` has a top-level volatile qualifier. This has a base characteristic of `bml::true_type`
if `T` has a top-level volatile qualifier, and `bml::false_type` otherwise.

Both `is_volatile` and `is_volatile_v` are similar to `std::is_volatile` and `std::is_volatile_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` has a top-level volatile qualifier.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
