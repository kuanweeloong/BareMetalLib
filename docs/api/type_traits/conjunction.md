# `<bml/type_traits/conjunction.hpp>`
#### Table of Contents
- [`conjunction`](#conjunction)

## `conjunction`
```c++
template <typename... Bs>
struct conjunction;

template <typename... Bs>
constexpr auto conjunction_v = bool(conjunction<Bs...>::value);
```
Forms the logical conjunction of `Bs...`. This has a public and unambiguous base that is:

- `bml::true_type` if `Bs...` is empty.
- The first type in `Bs...` for which `bool(B::value)` is `false`, if at least one such type exists.
- The last type in `Bs...` otherwise.

Effectively, this provides a static data member `value` that is `true` if `bool(B::value)` is `true`
for all types `B` in `Bs...`; otherwise, `value` is `false`.

The member names of the base class, other than `conjunction` and `operator=`, are not hidden and are
unambiguously available.

Note that this is short-circuiting; if `B` is the first type in `Bs...` for which
`bool(B::value)` is `false`, then `conjunction<Bs...>` will not require the instantiation of any
type after `B`.

Both `conjunction` and `conjunction_v` are similar to `std::conjunction` and `std::conjunction_v`,
respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `Bs...` is empty.
- The first type in `B` in `Bs...` for which `bool(B::value)` is `false`, if at least one such type
  exists.
- The last type in `Bs...` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
