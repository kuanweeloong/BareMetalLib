# `<bml/type_traits/aligned_union.hpp>`
#### Table of Contents
- [`aligned_union`](#aligned_union)

## `aligned_union`
```c++
template <ptrdiff_t Len, typename... Ts>
struct aligned_union;

template <ptrdiff_t Len, typename... Ts>
using aligned_union_ty = typename aligned_union<Len, Ts...>::type;
```
Creates a type suitable for use as object storage for objects of any type in `Ts...`. This provides
a member type alias `type` which names a trivial, standard-layout type that can be used as
uninitialized storage for any object whose type is named in `Ts...`. The size of `type` is at least
`Len`, and its alignment is equal to the strictest alignment of all types in `Ts...`.

This supports all platform-supported extended alignment requirements.

If `Ts...` is empty, or there are incomplete types in `Ts...`, program behaviour is undefined.

Both `aligned_union` and `aligned_union_ty` are similar to `std::aligned_union` and
`std::aligned_union_t`, respectively, except that they use `ptrdiff_t` for `Len` instead of
`size_t`, and that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names a trivial, standard-layout type that can be used as uninitialized storage for any object whose
type is named in `Ts...`; its size is at least `Len`, and its alignment is equal to the strictest
alignment of all types in `Ts...`.

#### Static member constants
```c++
static constexpr auto alignment_value = ptrdiff_t(/* ... */);
```
Equal to the strictest alignment requirement of all types in `Ts...`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
