# `<bml/type_traits/negation.hpp>`
#### Table of Contents
- [`negation`](#negation)

## `negation`
```c++
template <typename B>
struct negation;

template <typename B>
constexpr auto negation_v = bool(negation<B>::value);
```
Forms the logical negation of `B`. This has a base characteristic of
`bml::bool_constant<!bool(B::value)>`.

Effectively, this provides a static data member `value` that is `true` if `bool(B::value)` is
`false`, and `false` otherwise.

Both `negation` and `negation_v` are similar to `std::negation` and `std::negation_v`, respectively.

#### Public base classes
```c++
bml::bool_constant<!bool(B::value)>
```

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
