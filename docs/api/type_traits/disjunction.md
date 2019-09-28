# `<bml/type_traits/disjunction.hpp>`
#### Table of Contents
- [`disjunction`](#disjunction)

## `disjunction`
```c++
template <typename... Bs>
struct disjunction;

template <typename... Bs>
constexpr auto disjunction_v = bool(disjunction<Bs...>::value);
```
Forms the logical disjunction of `Bs...`. This has a public and unambiguous base that is:

- `bml::false_type` if `Bs...` is empty.
- The first type in `Bs...` for which `bool(B::value)` is `true`, if at least one such type exists.
- The last type in `Bs...` otherwise.

Effectively, this provides a static data member `value` that is `true` if `bool(B::value)` is `true`
for at least one type `B` in `Bs...`; otherwise, `value` is `false`.

The member names of the base class, other than `disjunction` and `operator=`, are not hidden and are
unambiguously available.

Note that this is short-circuiting; if `B` is the first type in `Bs...` for which
`bool(B::value)` is `false`, then `disjunction<Bs...>` will not require the instantiation of any
type after `B`.

Both `disjunction` and `disjunction_v` are similar to `std::disjunction` and `std::disjunction_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::false_type` if `Bs...` is empty.
- The first type in `B` in `Bs...` for which `bool(B::value)` is `true`, if at least one such type
  exists.
- The last type in `Bs...` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
