# `<bml/type_traits/is_pod.hpp>`
#### Table of Contents
- [`is_pod`](#is_pod)

## `is_pod`
```c++
template <typename T>
struct is_pod;

template <typename T>
constexpr auto is_pod_v = bool(is_pod<T>::value);
```
Checks if `T` is a POD type ("plain-old-data" - i.e. both trivial and standard layout). This has a
base characteristic of `bml::true_type` if `T` is a POD type, and `bml::false_type` otherwise.

If `bml::remove_all_extents_ty<T>` is an incomplete type other than (possibly cv-qualified) `void`,
program behaviour is undefined.

Both `is_pod` and `is_pod_v` are similar to `std::is_pod` and `std::is_pod_v`, respectively.

#### Public base classes
```c++
/* See comments. */
```
Defined as follows:

- `bml::true_type` if `T` is a POD type.
- `bml::false_type` otherwise.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
