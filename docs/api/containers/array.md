# `<bml/containers/array.hpp>`
#### Table of Contents
- [`array`](#array)
- [`tuple_size<array>`](#tuple_sizearray)
- [`tuple_element<array>`](#tuple_elementarray)

## `array`
```c++
template <typename T, ptrdiff_t Len>
class array;
```
A container representing fixed size arrays containing `Len` contiguous objects of type `T`.

If `Len < 0`, the program is ill-formed.

This is similar to `std::array`.

#### Deduction Guides
```c++
template <typename T, typename... Args>>
array(T, Args...) -> array<T, pack_size_v<Args...> + 1>;
```
This deduces an `array` containing `N` objects of type `T`, where `N` is the number of
initialization arguments and `T` is the type of the arguments.

If the initialization arguments are not of the same type (i.e. `bml::is_same_v<Ts...>` is `false`),
the program is ill-formed.

#### Constructors
No constructors are defined for `array` - instead, `array` is an aggregate type, so aggregate
initialization should be used to initialize a new `array`.

#### Special member functions
```c++
constexpr array(array const& other) noexcept;
```
Copy constructs an `array` from `other`. This initializes each element of the new `array` from its
corresponding element in `other` by direct-initialization with `other[i]`, where `i` is the
element's index.

This is trivial if `Len == 0` or if `bml::is_trivially_copy_constructible_v<T>` is `true`.
Otherwise, this is deleted if `bml::is_copy_constructible_v<T>` is `false`.

```c++
constexpr array(array&& other) noexcept;
```
Move constructs an `array` from `other`. This initializes each element of the new `array` from its
corresponding element in `other` by direct-initialization with `bml::move(other[i])`, where `i` is
the element's index.

This is trivial if `Len == 0` or if `bml::is_trivially_move_constructible_v<T>` is `true`.
Otherwise, this does not participate in overload resolution (i.e. is not declared) if
`bml::is_move_constructible_v<T>` is `false`.

```c++
constexpr auto operator=(array const& other) noexcept -> array&;
```
Copy assigns this `array` from `other`. This assigns each element of this `array` from its
corresponding element in `other` via `(*this)[i] = other[i]`, where `i` is the element's index.

This is trivial if `Len == 0` or if `bml::is_trivially_copy_assignable_v<T>` is `true`. Otherwise,
this is deleted if `bml::is_copy_assignable_v<T>` is `false`.

```c++
constexpr auto operator=(array&& other) noexcept -> array&;
```
Move assigns this `array` from `other`. This assigns each element of this `array` from its
corresponding element in `other` via `(*this)[i] = bml::move(other[i])`, where `i` is the element's
index.

This is trivial if `Len == 0` or if `bml::is_trivially_move_assignable_v<T>` is `true`. Otherwise,
this does not participate in overload resolution (i.e. is not declared) if
`bml::is_move_assignable_v<T>` is `false`.

```c++
~array();
```
Destroys this `array` and all its elements.

This is trivial if `Len == 0` or if `bml::is_trivially_destructible_v<T>` is `true`. Otherwise, this
is deleted if `bml::is_destructible_v<T>` is `false`.

#### Member functions
```c++
[[nodiscard]] constexpr auto size() const noexcept -> ptrdiff_t
```
Returns `Len`, the length of this `array`.

```c++
[[nodiscard]] constexpr auto max_size() const noexcept -> ptrdiff_t
```
Returns `Len`, the length of this `array`.

```c++
[[nodiscard]] constexpr auto empty() const noexcept -> bool
```
Returns `true` if `Len != 0`, and `false` otherwise.

```c++
[[nodiscard]] constexpr auto operator[](ptrdiff_t i) & noexcept -> T&;

[[nodiscard]] constexpr auto operator[](ptrdiff_t i) && noexcept -> T&&;

[[nodiscard]] constexpr auto operator[](ptrdiff_t i) const & noexcept -> T const&;

[[nodiscard]] constexpr auto operator[](ptrdiff_t i) const && noexcept -> T const&&;
```
Returns a reference to the `i`-th element of this `array`.

The program is ill-formed if this is invoked when `Len == 0`. Program behaviour is undefined if `i`
is not within this `array`'s bounds (i.e. `i < 0` or `i >= Len`).

```c++
template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() & noexcept -> T&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() && noexcept -> T&&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const & noexcept -> T const&;
    
template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const && noexcept -> T const&&;
```
Returns a reference to the `I`-th element of this `array`.

The program is ill-formed if this is invoked when `Len == 0`, or if `I` is not within this `array`'s
bounds (i.e. `I < 0` or `I >= Len`).

```c++
[[nodiscard]] constexpr auto front() & noexcept -> T&;

[[nodiscard]] constexpr auto front() && noexcept -> T&&;

[[nodiscard]] constexpr auto front() const & noexcept -> T const&;

[[nodiscard]] constexpr auto front() const & noexcept -> T const&&;
```
Returns a reference to the first element of this `array`.

The program is ill-formed if this is invoked when `Len == 0`.

```c++
[[nodiscard]] constexpr auto back() & noexcept -> T&;

[[nodiscard]] constexpr auto back() && noexcept -> T&&;

[[nodiscard]] constexpr auto back() const & noexcept -> T const&;

[[nodiscard]] constexpr auto back() const & noexcept -> T const&&;
```
Returns a reference to the last element of this `array`.

The program is ill-formed if this is invoked when `Len == 0`.

```c++
[[nodiscard]] constexpr auto data() noexcept -> T*;

[[nodiscard]] constexpr auto data() const noexcept -> T const*;
```
Returns a pointer to the underlying array serving as element storage for this `array`. The returned
pointer will always point to the first element of this `array`.

The program is ill-formed if this is invoked when `Len == 0`.

```c++
constexpr auto fill(T const& val) noexcept -> void
```
Copy-assigns `val` to all elements in this `array`.

The program is ill-formed if this is invoked when `Len == 0`.

```c++
constexpr auto swap(array& other) noexcept -> void;
```
Swaps this `array`'s elements with `other`'s elements. The `i`-th element of this `array` is swapped
with the `i`-th element of `other` via:

> ```c++
> using bml::swap;
> swap((*this)[i], other[i]);
> ```

This does not participate in overload resolution unless `Len == 0` or `bml::is_swappable_v<T>` is
`true`.

#### Associated free functions
```c++
template <ptrdiff_t I, typename T, ptrdiff_t Len>
[[nodiscard]] constexpr auto get(array<T, Len>& a) noexcept -> T&;

template <ptrdiff_t I, typename T, ptrdiff_t Len>
[[nodiscard]] constexpr auto get(array<T, Len> const& a) noexcept -> T const&;

template <ptrdiff_t I, typename T, ptrdiff_t Len>
[[nodiscard]] constexpr auto get(array<T, Len>&& a) noexcept -> T&&;

template <ptrdiff_t I, typename T, ptrdiff_t Len>
[[nodiscard]] constexpr auto get(array<T, Len> const&& a) noexcept -> T const&&;
```
Returns a reference to the `I`-th element of `a`.

The program is ill-formed if `I` is not within `a`'s bounds (i.e. `I < 0` or `I >= Len`).

This is similar to the index-based `std::get` for `array`s, except that it uses `ptrdiff_t` for the
index instead of `size_t`.

```c++
template <typename T, ptrdiff_t Len>
constexpr auto swap(array<T, Len>& lhs, array<T, Len>& rhs) noexcept -> void;
```
Swaps `lhs`'s elements with `rhs`'s elements. The `i`-th element of `lhs` is swapped with the `i`-th
element of `rhs` via:

> ```c++
> using bml::swap;
> swap(lhs[i], rhs[i]);
> ```

This does not participate in overload resolution unless `Len == 0` or `bml::is_swappable_v<T>` is
`true`.

This is similar to `std::swap` for `array`s.

## `tuple_size<array>`
```c++
template <typename T, ptrdiff_t Len>
struct tuple_size<array<T, Len>>;
```
A specialization of `tuple_size` for `array` which yields the length, `Len`, of the argument
`array`.

If `Len` is larger than `PTRDIFF_MAX`, the program is ill-formed.

This is simlar to the specialization of `std::tuple_size` for `std::array`.

## `tuple_element<array>`
```c++
template <ptrdiff_t I, typename T, ptrdiff_t Len>
struct tuple_element<I, array<T, Len>>;
```
A specialization of `tuple_element` for `array` which yields the type of the objects, `T`, stored in
the argument `array`. This will always yield `T` regardless of the value of `I`, as long as `I` is
within the `array`'s bounds (i.e `0 <= I < Len`).

If `I` is not within the `array`'s bounds, the program is ill-formed.

This is simlar to the specialization of `std::tuple_element` for `std::array`.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
