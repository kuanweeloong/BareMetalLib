# `<bml/type_traits/type_pack_element.hpp>`
#### Table of Contents
- [`type_pack_element`](#type_pack_element)

## `type_pack_element`
```c++
template <ptrdiff_t N, typename... Ts>
struct type_pack_element;

template <ptrdiff_t N, typename... Ts>
using type_pack_element_ty = typename type_pack_element<N, Ts...>::type;
```
Obtains the `N`-th type in the template type parameter pack `Ts...`. This provides a member type
alias `type` which names the `N`-th type in `Ts...`. If `N` is larger than or equal to
`bml::pack_size_v<Ts...>`, there is no member `type`.

If `N` is negative, the program is ill-formed.

#### Member type aliases
```c++
using type = /* ... */;
```
Names the `N`-th type in `Ts...`. If `N` is larger than or equal to `bml::pack_size_v<Ts...>`, this
alias is unavailable.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
