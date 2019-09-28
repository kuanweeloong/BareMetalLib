# `<bml/utilities/new.hpp>`
#### Table of Contents
- [`operator new`](#-operator-new-)

## `operator new`
```c++
[[nodiscard]] auto operator new(::size_t size, void* ptr) noexcept -> void*;
```
Provides a declaration of global placement `operator new`.

No definition provided for this; doing so would cause program behaviour to be undefined.

---
*This documentation is licensed under [CC BY-SA 4.0][1]. It includes content adapted from
[cppreference.com][2], which is licensed under [CC BY-SA 3.0][3].*

[1]: https://creativecommons.org/licenses/by-sa/4.0
[2]: https://en.cppreference.com
[3]: https://creativecommons.org/licenses/by-sa/3.0
