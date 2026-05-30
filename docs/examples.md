# Examples

All samples are built alongside the library. From the `build/` directory:

```bash
cmake --build .
# executables are placed in build/
```

---

## `draw` — Random Pixel Art

Fills a 10×10 `Image` with random colors from the 16-terminal-color palette and draws it at a random screen position.

**Key API used:** `Image`, `Image::SetColor`, `TUIA::Draw(Point, Image)`

```cpp
TUIA::Init();
Image img{10, 10};
img.SetColor({i, j}, Color(255, 255, 255)); // fill with white first
img.SetColor({i, j}, colors[rand() % colors.size()]); // randomize
TUIA::Draw({x, y}, img);
```

---

## `draw_colors` — 16-Color Palette Reference

Displays all 16 classic terminal colors as labeled rows, showing the color name as text on its own background.

**Key API used:** `TUIA::SetBackgroundColor(Color)`, `TUIA::SetForegroundColor(Color)`, `TUIA::WriteLine`

```cpp
TUIA::SetBackgroundColor(colors[i]);
TUIA::SetForegroundColor(Color(0, 0, 0));
TUIA::WriteLine({1, i}, colors[i].ToString());
```

---

## `screen` — Color Cycling Animation

Animates a sequence of colored nested rectangles that shrink toward the center. Runs 3 rounds, cycling through 7 background colors with a 300 ms delay between frames.

**Key API used:** `TUIA::ClearBlock(Point, Point)`, `TUIA::SetBackgroundColor`, `TUIA::SetCursor`

```cpp
TUIA::SetBackgroundColor(colors[i]);
TUIA::ClearBlock({i+1, i+1}, {width-i-1, height-i-1});
sleep_for(milliseconds(300));
```

---

## `change_screens` — Frame-by-Frame Sprite Animation

Creates 20 `Image` frames (40×20 each), each with a single white pixel advancing diagonally, and plays them back at 50 ms per frame.

**Key API used:** `Image`, `Image::SetColor`, `TUIA::Draw(Image)`, `std::this_thread::sleep_for`

```cpp
std::vector<Image> images(20, Image(40, 20, BackgroundColor::BrightBlack));
images[i].SetColor({i, i}, Color(255, 255, 255));
TUIA::Draw(images[i]);
```

---

## `moved_point` — Pong-Like Game (Multithreaded)

A 60×23 bouncing-ball game. The ball bounces off walls and the player-controlled paddle. Three threads run simultaneously: one for keyboard input, one for drawing, and one for quit detection.

**Key API used:** `Image`, `Image::SetColor`, `TUIA::Draw(Image)`, `TUIA::WriteLine`, `std::mutex`

Controls:
- **← / →**: Move paddle left / right
- **Q**: Quit

```cpp
std::mutex mutex;   // protects shared game state
std::thread(movePalette).detach();
std::thread(draw).detach();
quit(); // blocks main thread
```

---

## `ui` — Dialog Box Component

Demonstrates a reusable `DialogBox` class built with TUIA primitives: a blue background block, white text border, title, message, and an OK button — all centered on the screen.

**Key API used:** `TUIA::DrawBlock`, `TUIA::DrawBlock(BackgroundColor)`, `TUIA::WriteLine`, `TUIA::SetCursor`

```cpp
DialogBox box("Dialog Box", "This is a dialog box.", "OK");
box.Draw();
```

---

## `text_image` — ASCII Car Animation

Loads a 16-line ASCII-art car into a `TextImage` and scrolls it across the screen horizontally.

**Key API used:** `TextImage`, `TextImage::SetSymbol`, `TUIA::Draw(TextImage)`, `std::this_thread::sleep_for`

```cpp
TextImage img(80, 20);
SetCar(img, {x, 2}); // writes car characters into the image
TUIA::Draw(img);
```

---

## `ascii_painter` — Interactive ASCII Art Editor

Full interactive painting application. The user moves a cursor with keyboard and places ASCII symbols. Images can be saved to file.

**Key API used:** `Image`, `Image::SetSymbol`, `Image::SetColor`, `TUIA::Draw(Point, Image)`, `TUIA::GetCursor`, `TUIA::SetCursor`, `Image::Save`

Supported keys:

| Key | Action |
|-----|--------|
| `w` / ↑ | Move cursor up |
| `a` / ← | Move cursor left |
| `s` / ↓ | Move cursor down |
| `d` / → | Move cursor right |
| `c` | Clear screen |
| `q` | Quit |
| `1` | Save image (prompted filename) |
| `2` | Save image (auto filename) |

Drawing symbols:

```cpp
const char VERTICAL   = '|';
const char HORIZONTAL = '-';
const char CORNER     = '+';
const char EMPTY      = ' ';
const char SOLID      = '#';
const char SLASH      = '/';
const char BACKSLASH  = '\\';
const char DOT        = '.';
const char STAR       = '*';
const char UNDERSCORE = '_';
const char CIRCLE     = 'O';
```

