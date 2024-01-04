# TUIA library

Text user interface library. Defined in the `usm::graphics` namespace.

## Dependencies

* `gcc` - recommended C++ compiler, version 8 and up;
* `make` - make tool, recommended version 4 and up.

## Build

SHow usage:

```shell
make help
```

Build library:

```shell
make
```

## Interface

```cpp
class TUIA
{
public:
    static std::string ColorCode(ForegroundColor fgColor, BackgroundColor bgColor);
    static void Init();
    static void SetForegroundColor(const Color &foregroundColor);
    static void SetBackgroundColor(const Color &backgroundColor);
    static void SetForegroundColor(const ForegroundColor &foregroundColor);
    static void SetBackgroundColor(const BackgroundColor &backgroundColor);
    static Color GetForegroundColor();
    static Color GetBackgroundColor();
    static void WriteLine(const Point &position, const std::string &line);
    static void ClearLine(const Point &position, uint32_t nChars);
    static void ClearBlock(const Point &leftTop, const Point &rightBottom);
    static void ClearBlock(const Point &position, uint32_t nChars, uint32_t nLines);
    static void ClearScreen();
    static void Draw(const Point &position, const Image &image);
    static void SetCursor(const Point &position);
    static Point GetScreenSize();
    static void PutPoint(const Point& position, const Color& color);
    static void PutPoint(const Point& position, const BackgroundColor& color);
};
```

## Usage

```cpp

using usm::graphics::TUIA;
using usm::graphics::Point;
using usm::graphics::Color;

TUIA::Init();
TUIA::ClearScreen();
TUIA::ClearBlock({2, 2}, {20, 5});
TUIA::WriteLine({2, 3}, "This is a test");
```
