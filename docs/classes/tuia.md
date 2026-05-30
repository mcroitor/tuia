# TUIA

Static utility class providing a common API for drawing text and block-color graphics in the terminal. All methods are `static`. Defined in `tuia.hpp`, namespace `usm::graphics`.

## Interface

```cpp
class TUIA
{
public:
    static std::string ColorCode(ForegroundColor fgColor, BackgroundColor bgColor);
    static void SetColors(const ForegroundColor& foregroundColor, const BackgroundColor& backgroundColor);
    static void Init();
    static void FullScreen();
    static void SetWindowSize(int width, int height);

    static void SetForegroundColor(const Color& foregroundColor);
    static void SetBackgroundColor(const Color& backgroundColor);
    static void SetForegroundColor(const ForegroundColor& foregroundColor);
    static void SetBackgroundColor(const BackgroundColor& backgroundColor);
    static Color GetForegroundColor();
    static Color GetBackgroundColor();

    static void WriteLine(const Point& position, const std::string& line);
    static void ClearLine(const Point& position, int nChars);
    static void ClearBlock(const Point& leftTop, const Point& rightBottom);
    static void ClearBlock(const Point& position, int nChars, int nLines);
    static void ClearScreen();

    static void Draw(const Point& position, const Image& image);
    static void Draw(const Image& image);
    static void Draw(const TextImage& image);
    static void DrawBlock(const Point& leftTop, int nChars, int nLines, const Color& color);
    static void DrawBlock(const Point& leftTop, int nChars, int nLines, const BackgroundColor& color);

    static void PutPoint(const Point& position, const Color& color);
    static void PutPoint(const Point& position, const BackgroundColor& color);

    static void SetCursor(const Point& position);
    static Point GetCursor();
    static Point GetScreenSize();

    static void ResetColors();
    static void Flush();
    static void BeginFrame();
    static void EndFrame();
};
```

## Methods

### `static void Init()`

Initializes the terminal for TUIA use. Must be called once before any other TUIA method. Enables virtual terminal processing on Windows, resets colors to White-on-Black, and clears the screen.

### `static std::string ColorCode(ForegroundColor fgColor, BackgroundColor bgColor)`

Returns the ANSI escape sequence string that sets the given foreground and background colors. Does not write to the terminal.

### `static void SetColors(const ForegroundColor& fg, const BackgroundColor& bg)`

Sets both foreground and background colors at once and writes the escape sequence to the terminal.

### `static void SetForegroundColor(const ForegroundColor& color)`
### `static void SetForegroundColor(const Color& color)`

Sets the foreground (text) color. The `Color` overload converts via `ToForegroundColor()`.

### `static void SetBackgroundColor(const BackgroundColor& color)`
### `static void SetBackgroundColor(const Color& color)`

Sets the background color. The `Color` overload converts via `ToBackgroundColor()`.

### `static Color GetForegroundColor()`
### `static Color GetBackgroundColor()`

Returns the currently active foreground or background color as a `Color` (RGB) value.

### `static void ResetColors()`

Resets foreground to White and background to Black.

### `static void FullScreen()`

Maximizes the console window (Windows) or switches to the alternate screen buffer (Linux).

### `static void SetWindowSize(int width, int height)`

Resizes the console window in pixels (Windows only).

### `static void WriteLine(const Point& position, const std::string& line)`

Writes `line` at the given screen position using the current colors.

### `static void ClearLine(const Point& position, int nChars)`

Overwrites `nChars` characters starting at `position` with spaces.

### `static void ClearBlock(const Point& leftTop, const Point& rightBottom)`
### `static void ClearBlock(const Point& position, int nChars, int nLines)`

Clears a rectangular region of the screen by filling it with spaces using the current background color.

### `static void ClearScreen()`

Clears the entire visible terminal screen.

### `static void Draw(const Point& position, const Image& image)`

Draws `image` with its top-left corner at `position`.

### `static void Draw(const Image& image)`

Draws `image` starting at position (0, 0).

### `static void Draw(const TextImage& image)`

Draws a `TextImage` (monochrome character art) starting at position (0, 0).

### `static void DrawBlock(const Point& leftTop, int nChars, int nLines, const BackgroundColor& color)`
### `static void DrawBlock(const Point& leftTop, int nChars, int nLines, const Color& color)`

Fills a `nChars × nLines` rectangle starting at `leftTop` with the given color.

### `static void PutPoint(const Point& position, const Color& color)`
### `static void PutPoint(const Point& position, const BackgroundColor& color)`

Draws a single colored "pixel" (one terminal cell filled with a space) at `position`.

### `static void SetCursor(const Point& position)`

Moves the terminal text cursor to `position`.

### `static Point GetCursor()`

Returns the current cursor position. Uses the Win32 console API on Windows and the ANSI `ESC[6n` DSR sequence on Linux.

### `static Point GetScreenSize()`

Returns the visible terminal dimensions as a `Point` where `X` = width (columns) and `Y` = height (rows).

### `static void Flush()`

Flushes the stdout buffer (`fflush(stdout)`).

### `static void BeginFrame()`

Starts accumulating all subsequent draw calls into an internal frame buffer instead of writing directly to stdout. Use together with `EndFrame()` to eliminate screen flicker in animation loops.

```cpp
while (running) {
    TUIA::BeginFrame();
    TUIA::ClearScreen();
    TUIA::Draw(Point(x, y), sprite);
    TUIA::EndFrame();   // single atomic write to terminal
}
```

### `static void EndFrame()`

Flushes the frame buffer accumulated since `BeginFrame()` to stdout in a single `fwrite` call, then resets the buffer. Must be preceded by `BeginFrame()`.

