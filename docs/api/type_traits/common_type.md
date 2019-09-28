# `<bml/type_traits/common_type.hpp>`
#### Table of Contents
- [`common_type`](#common_type)

## `common_type`
```c++
template <typename... Ts>
struct common_type;

template <typename... Ts>
using common_type_ty = typename common_type<Ts...>::type;
```
Determines the common type between all types in `Ts...` (i.e. a type which all those types can be
converted to). Note that such a type may not exist.

This provides a member type alias `type` which names the common type between all types in `Ts...` if
it exists. Otherwise, this does not define any member `type`.

The common type is determined using the rules below:

- If `Ts...` is empty, there is no common type.
- If there is only one type in `Ts...`, let `T` refer to that sole type. Then the common type is
  the type named by `common_type<T, T>::type` if it exists; if it does not, there is no common type.
- If there are two types in `Ts...`, let `T1` and `T2` refer to the first and second type in
  `Ts...`, and let `D1` and `D2` name the same type as `bml::decay_ty<T1>` or `bml::decay_ty<T2>`,
  respectively. Then:
  - If either `D1` or `D2` does not name the same type as `T1` and `T2`, respectively, the common
    type is the type named by `common_type<D1, D2>::type` if it exists; if it does not, there is
    no common type.
  - Otherwise, if there is a user-provided specialization of `common_type<T1, T2>`, the common
    type is the type named by `common_type<T1, T2>::type` if it exists; if it does not, there is
    no common type.
  - Otherwise, let `C` name the same type as
    `decltype(false ? bml::declval<D1>() : bml::declval<D2>())`. If `C` names a valid type, the
    common type is the type named by `bml::decay_ty<C>`; if `C` is not a valid type, there is no
    common type.
- If there are more than two types in `Ts...`, let `T1` and `T2` refer to the first and second
  types in `Ts...`, and `R...` refer to the pack of remaining types. Then:
  - If `common_type<T1, T2>::type` does not exist, there is no common type.
  - Otherwise, let `C` name the same type as `common_type<T1, T2>::type`. Then, the common type is
    the type named by `common_type<C, R...>::type`, if it exists; if it does not, there is no common
    type.

Program behaviour is undefined if any of the conditions below are met:

- Any type in `Ts...` is an incomplete type other than (possibly cv-qualified) `void` or an array
  of unknown bound.
- An instantiation of a template above depends (directly or indirectly) on an incomplete type, and
  that instantiation could yield a different result if that type were hypothetically completed.

Note that users are allowed to specialize `common_type<T1, T2>` for types `T1` and `T2` if:

- At least one of `T1` and `T2` depends on a user-defined type.
- `bml::decay_ty<T1>` and `bml::decay_ty<T2>` name the same type as `T1` and `T2`, respectively.

User-provided specializations of `common_type<T1, T2>` must also satisfy the following requirements:

- If `common_type<T1, T2>` defines a member named `type`, then:
  - `type` must be a type alias which names a public and unambiguous cv-unqualified, non-reference
    type to which both `T1` and `T2` are explicitly convertible.
  - `common_type<T1, T2>::type` names the same type as `common_type<T2, T1>::type`
- Otherwise, both `common_type<T1, T2>` and `common_type<T2, T1>` must not have a member named
  `type`.

If a user adds specializations of `common_type` in violation of the rules above, program behaviour
is undefined.

Both `common_type` and `common_type_ty` are similar to `std::common_type` and `std::common_type_t`,
respectively, except that the latter has been suffixed with `_ty` for POSIX compatibility

#### Member type aliases
```c++
using type = /* ... */;
```
Names the common type between all the types in `Ts...`. If such a type does not exist, this alias is
unavailable.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
