# `<bml/type_traits/alignment_of.hpp>`
#### Table of Contents
- [`alignment_of`](#alignment_of)

## `alignment_of`
```c++
template <typename T>
struct alignment_of;

template <typename T>
constexpr auto alignment_of_v = ptrdiff_t(alignment_of<T>::value);
```
Obtains the alignment of `T`. This has a base characteristic of
`bml::integral_constant<ptrdiff_t, A>`, where `A` is the alignment of `T`.

If `T`'s alignment is larger than `PTRDIFF_MAX`, the program is ill-formed.

Both `alignment_of` and `alignment_of_v` are similar to `std::alignment_of` and
`std::alignment_of_v`, respectively, except that they expose the alignment as `ptrdiff_t` instead of
`size_t`.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, A>
```
`A` is the alignment of `T`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
