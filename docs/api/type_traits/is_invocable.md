# `<bml/type_traits/is_invocable.hpp>`
#### Table of Contents
- [`is_invocable`](#is_invocable)

## `is_invocable`
```c++
template <typename Fn, typename... ArgTypes>
struct is_invocable;

template <typename Fn, typename... ArgTypes>
constexpr auto is_invocable_v = bool(is_invocable<Fn, ArgTypes...>::value);
```
Checks if `Fn` is can be invoked with `ArgTypes...` via `bml::invoke`.  This has a base
characteristic of `bml::true_type` if the following expression is well-formed in an unevaluated
context:

> `bml::invoke(bml::declval<Fn>(), bml::declval<ArgTypes...>()...)`

Otherwise, this has a base characteristic of `bml::false_type`.

Both `is_invocable` and `is_invocable_v` are similar to `std::is_invocable` and
`std::is_invocable_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `Fn` can be invoked with `ArgTypes...` via `bml::invoke`.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
