# TODO

## Bugs

- [x] **BUG-01** — `#include` inside function body in `tuia.cpp` (Linux, blocks compilation)

**File:** `source/tuia.cpp` — `GetScreenSize()`  
**Severity:** Critical  
The Linux branch contains `#include <sys/ioctl.h>` inside the function body, which is invalid C++. This prevents the project from compiling on Linux.

```cpp
// Current (broken):
#elif __linux__
    #include <sys/ioctl.h>   // ❌ inside function body
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
```

**Fix:** Move `#include <sys/ioctl.h>` to the top of `tuia.cpp` inside a `#ifdef __linux__` guard.

---

- [x] **BUG-02** — `Image::GetWidth()` undefined behavior when height is 0

**File:** `source/image.cpp` — `GetWidth()`  
**Severity:** High  
`lines[0].size()` is called unconditionally, causing undefined behavior if the image was constructed with `height == 0`.

```cpp
int Image::GetWidth() const {
    return lines[0].size();  // ❌ UB if lines is empty
}
```

**Fix:** Guard with `if (lines.empty()) return 0;`

---

- [x] **BUG-03** — `Image::Load()` swaps width and height during resize

**File:** `source/image.cpp` — `Load()`  
**Severity:** High  
After reading `width` and `height` from file, the resize calls use them in swapped order, resulting in a transposed image structure:

```cpp
fin >> width >> height;
lines.resize(width, ...);    // ❌ should be height rows
symbols.resize(width, ...);  // ❌ should be height rows
```

**Fix:** Change both `resize` calls to use `height` as the row count and `width` as the column count.

---

- [x] **BUG-04** — `ascii_painter.cpp` uses `<termios.h>` unconditionally (Windows, blocks compilation)

**File:** `samples/ascii_painter.cpp`  
**Severity:** Critical  
The file includes `<termios.h>` and `<unistd.h>` at the top level without any platform guard. These headers do not exist on Windows. The custom `getch()` implementation using `tcgetattr`/`tcsetattr` also will not compile on Windows.

```cpp
#include <termios.h>   // ❌ not available on Windows
#include <unistd.h>    // ❌ not available on Windows
```

**Fix:** Wrap the Linux `getch()` implementation in `#ifdef __linux__` and add a `#ifdef _WIN32` branch using `_getch()` from `<conio.h>`.

---

- [x] **BUG-05** — `Image::Load()` has no error handling

**File:** `source/image.cpp` — `Load()`  
**Severity:** Medium  
If the file does not exist, cannot be opened, or is malformed, `Load()` silently proceeds with an empty/broken `ifstream`, resulting in undefined behavior.  
**Fix:** Check `fin.is_open()` after opening and handle the error (throw, return bool, or set a sentinel state).

---

## Missing Implementations

- [x] **MISSING-01** — `Image::DrawLine()` declared but never implemented

**File:** `source/image.hpp` / `source/image.cpp`  
**Severity:** Critical (linker error if called)  
`DrawLine(const Point& from, const Point& to, const BackgroundColor& color)` is declared in the header but has no definition in the `.cpp` file.  
**Fix:** Implement using Bresenham's line algorithm.

---

- [x] **MISSING-02** — `TUIA::GetCursor()` stub on Linux

**File:** `source/tuia.cpp` — `GetCursor()`  
**Severity:** Medium  
The Linux branch contains only a `// TODO: implement` comment and always returns `Point(0, 0)`.  
**Fix:** Implement using ANSI escape sequence `ESC[6n` combined with `tcgetattr`/`tcsetattr` to switch the terminal to raw mode temporarily and read the cursor position response.

---

- [ ] **MISSING-03** — `TUIA::SetWindowSize()` stub on Linux

**File:** `source/tuia.cpp` — `SetWindowSize()`  
**Severity:** Low  
The Linux branch is empty with only a comment `// resize terminal window`.  
**Fix:** Implement using the `resize` command or the `\033[8;<rows>;<cols>t` escape sequence.

---

## Code Quality Issues

- [x] **QUALITY-01** — `screen.cpp` sample has dead / commented-out logic

**File:** `samples/screen.cpp`  
The main animation loop is commented out with `int oops = 0; while (oops > 0) { ... }` which would also be unreachable even if uncommented. The file ends with a disconnected stub.  
**Fix:** Either restore the intended loop logic or remove the dead code.

---

- [x] **QUALITY-02** — Missing `#include <iostream>` in `tuia.cpp`

**File:** `source/tuia.cpp`  
`std::cout` is used without a direct `#include <iostream>`. It currently compiles only because of transitive includes through Windows headers.  
**Fix:** Add `#include <iostream>` explicitly.

---

## Test Coverage Gaps

- [x] **TEST-01** — `Image` class has zero test coverage

**File:** `tests/` (new file needed: `testimage.cpp`)  
No tests exist for `Image`: constructor, `GetWidth`/`GetHeight`, `SetColor`/`GetColor`, `SetSymbol`/`GetSymbol`, `In()`, `Clone()`, `Load()`/`Save()`, zero-dimension edge case.

---

- [x] **TEST-02** — `TextImage` class has zero test coverage

**File:** `tests/` (new file needed: `testtextimage.cpp`)  
No tests exist for `TextImage`: constructor, `GetPart`/`SetPart`, `Fill`, `Clear`, move semantics, `Load()`/`Save()`.

---

- [x] **TEST-03** — `Point` class has zero test coverage

**File:** `tests/testtuia.cpp` or a new `testpoint.cpp`  
No tests exist for `Point`: constructors, `GetX`/`GetY`, equality operator, copy semantics.

---

- [ ] **TEST-04** — `TUIA` tests are only informational

**File:** `tests/testtuia.cpp`  
Current tests only print screen size and cursor position — they do not assert any correctness. They should be expanded with actual assertions where possible (mocked or non-visual behavior).

---

## Development Proposals

- [x] **PROPOSAL-01** — Double-buffering for flicker-free animation

Samples like `change_screens.cpp` and `moved_point.cpp` are susceptible to visible flicker because they write directly to the terminal each frame. Adding a double-buffer mechanism in `TUIA` (render to string buffer, flush once per frame) would eliminate this.

---

- [x] **PROPOSAL-02** — Additional drawing primitives

`Image` currently only has `SetPixel` and the unimplemented `DrawLine`. Useful additions:

- `DrawRect(Point topLeft, int width, int height, BackgroundColor)` — filled or outline rectangle
- `DrawCircle(Point center, int radius, BackgroundColor)` — using midpoint circle algorithm
- `Fill(BackgroundColor)` — flood-fill entire image with a color

---

- [x] **PROPOSAL-03** — Typed file format versioning for `Image::Load`/`Save`

The current text-based format has no magic number or version header. Adding a version tag would allow safe format evolution and detect corrupted or wrong files early.

---

- [x] **PROPOSAL-04** — Complete API documentation for `TUIA` class

**File:** `docs/classes/tuia.md`  
Currently only `init()` is documented. All other public methods (`clear`, `draw`, `drawBlock`, `setCursor`, `getCursor`, `getScreenSize`, color methods) need API reference entries with signatures, parameter descriptions, and usage examples.

---

- [x] **PROPOSAL-05** — Complete `Color` class documentation

**File:** `docs/classes/color.md`  
Currently a single line. Needs full API reference: constructors, `R()`/`G()`/`B()`, `ToTerminal()`, `ToString()`, stream operators, and the quantization behavior of `ToTerminal()`.

---

- [x] **PROPOSAL-06** — Expand `examples.md` to cover all samples

**File:** `docs/examples.md`  
Only `ascii_painter` is mentioned. All 7 sample programs should be documented with their purpose and how to build/run them.
