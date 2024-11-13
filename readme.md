# TUIA library

Text user interface library. Defined in the `usm::graphics` namespace.

## Dependencies

* `gcc` - recommended C++ compiler, version 8 and up;
* `make` - make tool, recommended version 4 and up.

## Build

Show usage:

```shell
make help
```

Build library:

```shell
make
```

Or you can use cmake for building:

```shell
mkdir build
cd build
cmake ..
make
```

## Interface

The main class is `TUIA`. It provides a set of static methods for working with the text user interface.

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

Additional classes are used to represent colors and points.

```cpp
enum class ColorType {
    Black = 0x00000000,
    Red = 0x00FF0000,
    Green = 0x0000FF00,
    Blue = 0x000000FF,
    White = 0x00FFFFFF,
};

class Color
{
public:
    static uint32_t ExtractRed(uint32_t color);
    static uint32_t ExtractGreen(uint32_t color);
    static uint32_t ExtractBlue(uint32_t color);

    Color();
    Color(uint32_t color);
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(const Color &color);

    Color operator=(const Color &color);
    bool operator==(const Color &color) const;

    uint32_t Red() const;
    uint32_t Green() const;
    uint32_t Blue() const;
    uint32_t Value() const;
    std::string ToString() const;
    Color ToTerminal() const;
};
```

```cpp
class Point
{
public:
    Point();
    Point(int32_t x, int32_t y);
    Point(const Point &point);

    Point operator=(const Point &point);
    bool operator==(const Point &point) const;

    int32_t X() const;
    int32_t Y() const;
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
