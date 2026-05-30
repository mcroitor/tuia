# Color

Common class for RGB color representation. Defined in `color.hpp`, namespace `usm::graphics`.

## Interface

```cpp
class Color
{
public:
    // Static helpers
    static uint32_t ExtractRed(uint32_t color);
    static uint32_t ExtractGreen(uint32_t color);
    static uint32_t ExtractBlue(uint32_t color);

    // Constructors
    Color();
    Color(uint32_t value);
    Color(const Color& color);
    Color(uint8_t red, uint8_t green, uint8_t blue);

    // Accessors
    uint32_t Value() const;
    uint32_t Red()   const;
    uint32_t Green() const;
    uint32_t Blue()  const;

    // Conversion
    Color ToTerminal() const;
    std::string ToString() const;

    // Operators
    Color operator=(const Color& color);
    bool  operator==(const Color& color) const;
};

std::istream& operator>>(std::istream& in,  Color& color);
std::ostream& operator<<(std::ostream& out, const Color& color);
bool operator<(const Color& left, const Color& right);
```

## Methods

### `Color()`

Default constructor. Creates Black `(0, 0, 0)`.

### `Color(uint32_t value)`

Constructs a color from a packed 32-bit integer. Bits `[23:16]` = red, `[15:8]` = green, `[7:0]` = blue.

### `Color(uint8_t red, uint8_t green, uint8_t blue)`

Constructs a color from individual 8-bit channel values.

### `static uint32_t ExtractRed(uint32_t color)`
### `static uint32_t ExtractGreen(uint32_t color)`
### `static uint32_t ExtractBlue(uint32_t color)`

Extract a single channel from a packed 32-bit color value.

### `uint32_t Red() const`
### `uint32_t Green() const`
### `uint32_t Blue() const`

Return the individual channel values (0–255) of this color.

### `uint32_t Value() const`

Returns the packed 32-bit representation.

### `Color ToTerminal() const`

Quantizes each channel to one of four terminal-safe values: **0, 85, 170, 255**. This maps the full 24-bit RGB space onto the 4-level-per-channel subset that corresponds to the classic 16 ANSI terminal colors.

Example:
```cpp
Color(200, 100, 10).ToTerminal() // → Color(170, 85, 0)
```

### `std::string ToString() const`

Returns the color as a hexadecimal string, e.g. `"#ff8000"`.

### Stream operators `>>` / `<<`

Support reading and writing colors in hex format from/to streams. Used by `Image::Save()` and `Image::Load()`.

```cpp
Color c;
std::cin >> c;   // reads "#rrggbb"
std::cout << c;  // writes "#rrggbb"
```

### `bool operator<(const Color& left, const Color& right)`

Lexicographic ordering by (red, green, blue) — useful for using `Color` as a key in ordered containers.
