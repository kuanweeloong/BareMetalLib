# `<bml/type_traits/is_convertible.hpp>`
#### Table of Contents
- [`is_convertible`](#is_convertible)

## `is_convertible`
```c++
template <typename From, typename To>
struct is_convertible;

template <typename From, typename To>
constexpr auto is_convertible_v = bool(is_convertible<From, To>::value);
```
Checks if `From` is implicitly convertible to `To`. This has a base characteristic of
`bml::true_type` if the following function definition is well-formed in an unevaluated context:

> ```c++
> auto f() -> To
> {
>     return bml::declval<From>();
> }
> ```

Otherwise, this has a base characteristic of `bml::false_type`.

Program behaviour is undefined if any of the conditions below are met:

- `From` or `To` is an incomplete type other than (possibly cv-qualified) `void` or an array of
  unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Both `is_convertible` and `is_convertible_v` are similar to `std::is_convertible` and
`std::is_convertible_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is constructible from `Args...`.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
