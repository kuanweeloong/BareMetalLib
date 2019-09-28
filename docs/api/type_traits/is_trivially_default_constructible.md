# `<bml/type_traits/is_trivially_default_constructible.hpp>`
#### Table of Contents
- [`is_trivially_default_constructible`](#is_trivially_default_constructible)

## `is_trivially_default_constructible`
```c++
template <typename T>
struct is_trivially_default_constructible;

template <typename T>
constexpr auto is_trivially_default_constructible_v
    = bool(is_trivially_default_constructible<T>::value);
```
Checks if `T` is trivially default-constructible. This has a base characteristic of `bml::true_type`
if `bml::is_trivially_constructible_v<T>` is `true`, and `bml::false_type` otherwise.

Program behaviour is undefined if any of the conditions below are met:

- `T` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_trivially_default_constructible` and `is_trivially_default_constructible_v` are similar to
`std::is_trivially_default_constructible` and `std::is_trivially_default_constructible_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is trivially default-constructible.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
