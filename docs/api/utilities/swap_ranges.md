# `<bml/utilities/swap_ranges.hpp>`
#### Table of Contents
- [`swap_ranges`](#swap_ranges)

## `swap_ranges`
```c++
template <typename ForwardIt1, typename ForwardIt2>
constexpr auto swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) noexcept
    -> ForwardIt2;
```
Exchanges elements of the range `[first1, last1)` with elements of the range (of the same length)
starting at `first2`.

This iterates through both ranges and swaps `i`-th element of each range with each other. Let `e1`
and `e2` refer to the `i`-th element of the ranges starting at `first1` and `first2`, respectively.
Then swapping is done via:

> ```c++
> using bml::swap;
> swap(e1, e2);
> ```

Note that the program is ill-formed if any of the conditions below are met:

- Either `ForwardIt1` or `ForwardIt2` are not forward iterators of their respective ranges (i.e.
  they do not support the pre-increment or the indirection operator).
- `bml::is_swappable_with_v<T1, T2>` is `false`, where `T1` and `T2` name the type being iterated
  over by `ForwardIt1` and `ForwardIt2`, respectively.

This is similar to `std::swap_ranges`, except that this does not support execution policies.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
