# `<bml/type_traits/is_trivially_destructible.hpp>`
#### Table of Contents
- [`is_trivially_destructible`](#is_trivially_destructible)

## `is_trivially_destructible`
```c++
template <typename T>
struct is_trivially_destructible;

template <typename T>
constexpr auto is_trivially_destructible_v = bool(is_trivially_destructible<T>::value);
```
Checks if `T` is trivially destructible. This has a base characteristic of `bml::true_type` if
`bml::is_destructible_v<T>` is `true` and `bml::remove_all_extents_ty<T>` is either a non-class type
or a class type with a trivial destructor. Otherwise, this has a base characteristic of
`bml::false_type`.

Program behaviour is undefined if any of the conditions below are met:

- `T` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_trivially_destructible` and `is_trivially_destructible_v` are similar to
`std::is_trivially_destructible` and `std::is_trivially_destructible_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is trivially destructible.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
