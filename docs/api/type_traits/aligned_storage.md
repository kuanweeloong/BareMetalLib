# `<bml/type_traits/aligned_storage.hpp>`
#### Table of Contents
- [`aligned_storage`](#aligned_storage)

## `aligned_storage`
```c++
template <ptrdiff_t Len, ptrdiff_t Align = bml::alignment_of_v<max_align_t>>
struct aligned_storage;

template <ptrdiff_t Len, ptrdiff_t Align = bml::alignment_of_v<max_align_t>>
using aligned_storage_ty = typename aligned_storage<Len, Align>::type;
```
Creates a type suitable for use as object storage. This provides a member type alias `type` which
names a trivial, standard-layout type that can be used as uninitialized storage for any object whose
size is at most `Len`, and whose alignment is a divisor of `Align`.

The default value of `Align` is the most stringent (i.e. the largest) fundamental alignment
requirement for any object whose size is at most `Len`. However, this supports all
platform-supported extended alignment requirements.

If `Len == 0` or `Align` is not equal to the value of `bml::alignment_of_v(T)` for some type `T`,
program behaviour is undefined. If either `Align` or `Len` is negative, the program is ill-formed.

Both `aligned_storage` and `aligned_storage_ty` are similar to `std::aligned_storage` and
`std::aligned_storage_t`, respectively, except that:

- `ptrdiff_t` is used for for `Len` and `Align` instead of `size_t`.
- The default value of `Align` does not take into account over-aligned objects.
- The latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names a trivial, standard-layout type that can be used as uninitialized storage for any object whose
size is at most `Len`, and whose alignment is a divisor of `Align`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
