# `<bml/type_traits/is_swappable_with.hpp>`
#### Table of Contents
- [`is_swappable_with`](#is_swappable_with)

## `is_swappable_with`
```c++
template <typename T, typename U>
struct is_swappable_with;

template <typename T, typename U>
constexpr auto is_swappable_with_v = bool(is_swappable_with<T, U>::value);
```
Checks if `T` is swappable with `U`. This has a base characteristic of `bml::true_type` if both
expressions below are well-formed in an unevaluated context after `using bml::swap`:

- > `swap(bml::declval<T>(), bml::declval<U>())`
- > `swap(bml::declval<U>(), bml::declval<T>())`

Otherwise, this has a base characteristic of `bml::false_type`.

Program behaviour is undefined if any of the conditions below are met:

- `T` or `U` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown
  bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_swappable_with` and `is_swappable_with_v` are similar to `std::is_swappable_with` and
`std::is_swappable_with_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is swappable with `U`.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
