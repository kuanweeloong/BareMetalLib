# `<bml/type_traits/is_swappable.hpp>`
#### Table of Contents
- [`is_swappable`](#is_swappable)

## `is_swappable`
```c++
template <typename T>
struct is_swappable;

template <typename T>
constexpr auto is_swappable_v = bool(is_swappable<T>::value);
```
Checks if `T` is swappable. This has a base characteristic of `bml::true_type` if `T` is a
referenceable type and `bml::is_swappable_with_v<T&, T&>` is `true`.

Program behaviour is undefined if any of the conditions below are met:

- `T` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_swappable` and `is_swappable_v` are similar to `std::is_swappable` and
`std::is_swappable_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is swappable.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
