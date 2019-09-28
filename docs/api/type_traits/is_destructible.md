# `<bml/type_traits/is_destructible.hpp>`
#### Table of Contents
- [`is_destructible`](#is_destructible)

## `is_destructible`
```c++
template <typename T>
struct is_destructible;

template <typename T>
constexpr auto is_destructible_v = bool(is_destructible<T>::value);
```
Checks if `T` is destructible. This has a base characteristic of `bml::true_type` if:

- `T` is a reference type.
- `T` is an object type, and the following expression is well-formed in an unevaluated context
  (where `U` names the same type as `bml::remove_all_extents_ty<T>`):
  > `bml::declval<U&>().~U()`

Otherwise, this has a base characteristic of `bml::false_type`.

Program behaviour is undefined if any of the conditions below are met:

- `T` is an incomplete type other than (possibly cv-qualified) `void` or an array of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_destructible` and `is_destructible_v` are similar to `std::is_destructible` and
`std::is_destructible_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is destructible.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
