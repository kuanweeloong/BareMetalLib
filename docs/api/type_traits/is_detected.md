# `<bml/type_traits/is_detected.hpp>`
#### Table of Contents
- [`is_detected`](#is_detected)

## `is_detected`
```c++
template <template <typename...> typename Op, typename... Args>
struct is_detected;

template <template <typename...> typename Op, typename... Args>
constexpr auto is_detected_v = bool(is_detected<T>::value);
```
Checks if `T` is a non-union class type. This has a base characteristic of `bml::true_type` if
`Op<Args...>` names a valid type, and `bml::false_type` otherwise.

Both `is_detected` and `is_detected_v` are similar to `std::experimental::is_detected` and
`std::experimental::is_detected_v` (as detailed in Library Fundamentals TSv3) respectively, except
that the former is a struct instead of a type alias.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `Op<Args...>` names a valid type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
