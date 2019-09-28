# `<bml/containers/tuple.hpp>`
#### Table of Contents
- [`tuple_size`](#tuple_size)
- [`tuple_element`](#tuple_element)
- [`tuple`](#tuple)

## `tuple_size`
```c++
template <typename T>
struct tuple_size;

constexpr auto tuple_size_v = ptrdiff_t(tuple_size<T>::value);
```
Gets the number of elements in a `bml::tuple`. 

- If `bml::remove_cv_ty<T>` names `bml::tuple`, then this has a base characteristic of
  `bml::integral_constant<ptrdiff_t, N>`, where `N` is the number of elements in that `tuple`.
- Otherwise, this does not have a definition.

If the number of elements in the `tuple` named by `T` is larger than `PTRDIFF_MAX`, the program is
ill-formed.

Both `tuple_size` and `tuple_size_v` are similar to `std::tuple_size` and `std::tuple_size_v` for
`tuple`s, respectively, except that they expose the number of elements as `ptrdiff_t` instead of
`size_t`, and the former's specializations for cv-qualified `T` are not SFINAE friendly.

#### Public base classes
```c++
bml::integral_constant<ptrdiff_t, N>
```
`N` is the number of elements in the `tuple` named by `T`.

## `tuple_element`
```c++
template <ptrdiff_t I, typename T>
struct tuple_element;

template <ptrdiff_t I, typename T>
using tuple_element_ty = typename tuple_element<I, T>::type;
```
Gets the type of the `I`-th element in a `bml::tuple`.

- If `bml::remove_cv_ty<T>` names `bml::tuple`, then this provides a member type alias `type` which
  names the type of the `I`-th element in that `tuple` after combining its top-level cv-qualifiers
  with those of `T` (e.g. `tuple_element_ty<0, bml::tuple<int volatile> const>` names
  `int const volatile`).
- Otherwise, this does not have a definition.

If `I` is not in the range `[0, N)`, where `N` is the total number of elements in the `tuple` named
by `T`, the program is ill-formed.

Both `tuple_element` and `tuple_element_ty` are similar to `std::tuple_element` and
`std::tuple_element_t` for `tuple`s, respectively, except that they use `ptrdiff_t` for the index
instead of `size_t`, and that the latter has been suffixed with `_ty` for POSIX compatibility.

#### Member type aliases
```c++
using type = /* ... */;
```
Names the type of the `I`-th element in the `tuple` named by `T`, after combining its top-level
cv-qualifiers with `T`'s top-level cv-qualifiers.

## `tuple`
```c++
template <typename... Ts>
class tuple;
```
A container for storing a fixed-size collection of values. The `i`-th element of `Ts...` specifies
the type of the `i`-th element in the `tuple`.

This is similar to `std::tuple`, except that it does not support:

- uses-allocator construction
- construction or assignment from `pair`s (since `pair` is not a distinct BML type)
- structured bindings (since that requires specializing `std::tuple_size` and `std::tuple_element`,
  but BML does not assume that the C++ standard library is available).

#### Deduction Guides
```c++
template <typename... Ts>
tuple(Ts...) -> tuple<Ts...>;
```
This handles edge cases missed by the implicitly-generated deduction guides, such as
array-to-pointer conversion.

#### Constructors
```c++
constexpr tuple() noexcept;
```
Constructs a `tuple` and value-initializes each element.

This does not participate in overload resolution unless all elements of
`bml::is_default_constructible<Ts>...` are `true`. This is marked `explicit` if at least one element
of `bml::is_list_convertible<Ts>...` is `false`.

```c++
template <typename... Values>
constexpr tuple(Values&&... vs) noexcept;
```
Constructs a `tuple` and direct-initializes its `i`-th element with the `i`-th element of `vs...`
via `bml::forward<Vi>(vi)`, where `vi` and `Vi` refer to the `i`-th element of `vs...` and
`Values...`, respectively.

This does not participate in overload resolution unless all the conditions below are met:

- `sizeof...(Values) == sizeof...(Ts)`.
- All of `bml::is_constructible_v<Ts, Values>...` are `true`.

In addition, this is marked `explicit` if at least one element of
`bml::is_convertible_v<Ts, Values>...` is `false`.

#### Special member functions
```c++
constexpr tuple(tuple const& other) noexcept;
```
Copy constructs a `tuple` from `other`. This initializes each element of the new `tuple` from its
corresponding element in `other` by direct-initialization with `other.get<I>()`, where `I` is the
element's index.

This is trivial if all elements of `bml::is_trivially_copy_constructible_v<Ts>...` are `true`, and
deleted if at least one element of `bml::is_copy_constructible_v<Ts>...` is `false`.

```c++
constexpr tuple(tuple&& other) noexcept;
```
Move constructs a `tuple` from `other`. This initializes each element of the new `tuple` from its
corresponding element in `other` by direct-initialization with `bml::move(other.get<I>())`, where
`I` is the element's index.

This is trivial if all elements of `bml::is_trivially_move_constructible_v<Ts>...` are `true`, and
does not participate in overload resolution (i.e. is not declared) if at least one element of
`bml::is_move_constructible_v<Ts>...` is `false`.

```c++
constexpr auto operator=(tuple const& other) noexcept -> tuple&;
```
Copy assigns this `tuple` from `other`. This assigns each element of this tuple from its
corresponding element in `other` via `this->get<I>() = other.get<I>()`, where `I` is the
element's index.

This is trivial if all elements of `bml::is_trivially_copy_assignable_v<Ts>...` are `true`, and
deleted if at least one element of `bml::is_copy_assignable_v<Ts>...` is `false`.

```c++
constexpr auto operator=(tuple&& other) noexcept -> tuple&;
```
Copy assigns this `tuple` from `other`. This assigns each element of this tuple from its
corresponding element in `other` via `this->get<I>() = bml::move(other.get<I>())`, where `I` is the
element's index.

This is trivial if all elements of `bml::is_trivially_move_assignable_v<Ts>...` are `true`, and does
not participate in overload resolution (i.e. is not declared) if at least one element of
`bml::is_move_assignable_v<Ts>...` is `false`.

```c++
~tuple();
```
Destroys this `tuple` and all its elements.

This is trivial if all elements of `bml::is_trivially_destructible_v<Ts>...` are `true`, and deleted
if at least one element of `bml::is_destructible_v<Ts>...` is `false`.

#### Member functions
```c++
template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() & noexcept -> bml::tuple_element_ty<I, tuple>&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() && noexcept -> bml::tuple_element_ty<I, tuple>&&;

template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const & noexcept -> bml::tuple_element_ty<I, tuple> const&;
    
template <ptrdiff_t I>
[[nodiscard]] constexpr auto get() const && noexcept -> bml::tuple_element_ty<I, tuple> const&&;
```
Returns a reference to the `I`-th element in this `tuple`.

The program is ill-formed if `I` is negative or `sizeof...(Ts) >= I`.

```c++
constexpr auto swap(tuple& other) noexcept -> void;
```
Swaps this `tuple`'s elements with `other`'s elements. The `I`-th element of this `tuple` is swapped
with the `I`-th element of `other` via:

> ```c++
> using bml::swap;
> swap(this->get<I>(), other.get<I>());
> ```

This does not participate in overload resolution unless all elements of `bml::is_swappable_v<Ts>...`
are `true`.

#### Associated free functions
```c++
template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(tuple<Ts...>& t) noexcept
    -> bml::tuple_element_ty<I, tuple<Ts...>>&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(tuple<Ts...> const& t) noexcept
    -> bml::tuple_element_ty<I, tuple<Ts...>> const&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(tuple<Ts...>&& t) noexcept
    -> bml::tuple_element_ty<I, tuple<Ts...>>&&;

template <ptrdiff_t I, typename... Ts>
[[nodiscard]] constexpr auto get(tuple<Ts...> const&& t) noexcept
    -> bml::tuple_element_ty<I, tuple<Ts...>> const&&;
```
Returns a reference to the `I`-th element of `t`.

The program is ill-formed if `I` is negative or `sizeof...(Ts) >= I`.

This is similar to the index-based `std::get` for `tuple`s, except that it uses `ptrdiff_t` for the
index instead of `size_t`.

```c++
template <typename... Ts>
constexpr auto swap(tuple<Ts...>& lhs, tuple<Ts...>& rhs) noexcept -> void;
```
Swaps `lhs`'s elements with `rhs`'s elements. The `I`-th element of `lhs` is swapped with the `I`-th
element of `rhs` via:

> ```c++
> using bml::swap;
> swap(lhs.get<I>(), rhs.get<I>());
> ```

This does not participate in overload resolution unless all of `bml::is_swappable_v<Ts>...` are
`true`.

This is similar to `std::swap` for `tuple`s.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
