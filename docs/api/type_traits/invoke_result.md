# `<bml/type_traits/invoke_result.hpp>`
#### Table of Contents
- [`invoke_result`](#invoke_result)

## `invoke_result`
```c++
template <typename Fn, typename... ArgTypes>
struct invoke_result;

template <typename Fn, typename... ArgTypes>
using invoke_result_ty = typename invoke_result<Fn, ArgTypes...>::type;
```
Determines the return type when `Fn` is invoked with `ArgTypes...` via `bml::invoke`.

This provides a member type alias `type` which names the type (as deduced by `decltype`) of the
*invocation expression* used by `bml::invoke` when it is invoked in an unevaluated context via:

> `bml::invoke(bml::declval<Fn>(), bml::declval<ArgTypes>()...)`:

If the invocation expression is ill-formed, this does not define any member `type`.

For example, if `Fn` names a pointer to a function, `type` names
`decltype(bml::declval<Fn>()(bml::declval<ArgTypes>()...))` (since the expression within `decltype`
is `bml::invoke`'s invocation expression for pointers to functions).

If `Fn` or any type in `ArgTypes...` is an incomplete type other than (possibly cv-qualified) `void`
or an array of unknown bound, program behaviour is undefined.

Both `invoke_result` and `invoke_result_ty` are similar to `std::invoke_result` and
`std::invoke_result_t`, respectively, except that the latter has been suffixed with `_ty` for POSIX
compatibility.

#### Member type aliases
```c++
using type = /*...*/;
```
Names the return type when `Fn` is invoked with `ArgTypes...` via `bml::invoke`. If this would
result in an ill-formed *invocation expression*, this alias is unavailable.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
