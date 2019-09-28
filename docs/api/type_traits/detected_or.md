# `<bml/type_traits/detected_or.hpp>`
#### Table of Contents
- [`detected_or`](#detected_or)

## `detected_or`
```c++
template <typename Default, template <typename...> typename Op, typename... Args>
struct detected_or;

template <typename Default, template <typename...> typename Op, typename... Args>
using detected_or_ty = typename detected_or<Default, Op, Args...>::type;
```
Yields `Op<Args...>` if it names a valid type, and `Default` otherwise. This provides member type
aliases `type` and `value_ty` which name, respectively:

- `Op<Args...>` and `bml::true_type` if `Op<Args...>` names a valid type.
- `Default` and `bml::false_type` otherwise.

Both `detected_or` and `detected_or_ty` are similar to `std::experimental::detected_or` and
`std::experimental::detected_or_t` (as detailed in Library Fundamentals TSv3) respectively, except
that:

- The former is a struct instead of a type alias, and it provides `value_ty` instead of `value_t`
  to maintain POSIX compatibility.
- The latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names `Op<Args...>` if it names a valid type, and `Default` otherwise.

```c++
using value_ty = /* ... */;
```
Names `bml::true_type` if `Op<Args...>` names a valid type, and `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
