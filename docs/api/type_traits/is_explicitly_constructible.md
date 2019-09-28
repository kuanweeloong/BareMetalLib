# `<bml/type_traits/is_explicitly_constructible.hpp>`
#### Table of Contents
- [`is_explicitly_constructible`](#is_explicitly_constructible)

## `is_explicitly_constructible`
```c++
template <typename T, typename... Args>
struct is_explicitly_constructible;

template <typename T, typename... Args>
constexpr auto is_explicitly_constructible_v = bool(is_explicitly_constructible<T, Args...>::value);
```
Checks if `T` can only be explicitly constructed from `Args...`. This has a base characteristic of
`bml::true_type` if all the conditions below are met:

- `bml::is_constructible_v<T, Args...>` is `true`.
- `bml::is_list_convertible_v<T, Args...>` is `false`.

Otherwise, this has a base characteristic of `bml::false_type`.

Program behaviour is undefined if any of the conditions below are met:

- `T` or any type in `Args...` is an incomplete type other than (possibly cv-qualified) `void` or an
  array of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` can only be explicitly constructed from `Args...`.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
