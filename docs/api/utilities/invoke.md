# `<bml/utilities/invoke.hpp>`
#### Table of Contents
- [`invoke`](#invoke)

## `invoke`
```c++
template <typename F, typename... Args>
constexpr auto invoke(F&& f, Args&&... args) noexcept -> bml::invoke_result_ty<F, Args...>;
```
Invokes `f` with `args...` and returns the result.

Let `A0, A1, ..., An` be the expansion of `Args...`, and `a0, a1, ..., an` be the expansion of
`args...`. Then this performs invocation via an *invocation expression* defined as follows:

- If `f` is a pointer to a member function of class `T` and `bml::is_base_of<T, bml::decay_ty<A0>>`
  is `true`, invocation is done via:
  > `(a0.*f)(a1, ... an)`
- If `f` is a pointer to a member function of class `T` and `bml::decay_ty<A0>` names a
  specialization of `bml::reference_wrapper`, invocation is done via:
  > `(a0.get().*f)(a1, ... an)`
- If `f` is a pointer to a member function of class `T` and (1) and (2) does not apply, the
  invocation is done via:
  > `((*a0).*f)(a1, ... an)`
- If `f` is a pointer to a data member of class `T` and `bml::is_base_of<T, bml::decay_ty<A0>>` is
  `true`, and there are no other arguments apart from `a0`, invocation is done via:
  > `a0.*f`
- If `f` is a pointer to a data member of class `T` and `bml::decay_ty<A0>` names a specialization
  of `bml::reference_wrapper`, and there are no other arguments apart from `a0`, invocation is done
  via:
  > `a0.get().*f`
- If `f` is a pointer to a data member of class `T` and there are no other arguments apart from
  `a0`, and (4) and (5) does not apply, invocation is done via:
  > `(*a0).*f`
- If none of (1) - (6) apply, invocation is done via:
  > `f(a0, a1, ..., an)`

If the invocation expression is ill-formed, the program is ill-formed.

This is similar to `std::invoke`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
