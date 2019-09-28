# `<bml/type_traits/is_final.hpp>`
#### Table of Contents
- [`is_final`](#is_final)

## `is_final`
```c++
template <typename T>
struct is_final;

template <typename T>
constexpr auto is_final_v = bool(is_final<T>::value);
```
Checks if `T` is a final class type (i.e. a class that cannot be inherited from). This has a base
characteristic of `bml::true_type` if `T` is a final class type, and `bml::false_type` otherwise.

Program behaviour is undefined if `T` is an incomplete class type.

Both `is_final` and `is_final_v` are similar to `std::is_final` and `std::is_final_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a final class type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
