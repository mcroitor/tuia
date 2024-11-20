# Examples

## ASCII painter

Small program that allows you to draw ASCII art in the terminal.

Supported commands / keys:

- `w`, _arrow up_: Move cursor up
- `a`, _arrow left_: Move cursor left
- `s`, _arrow down_: Move cursor down
- `d`, _arrow right_: Move cursor right
- `c`: Clear the screen
- `q`: Quit the program
- `1`: Save image to specified file
- `2`: Save image with automatic name

To put a character on screen symbols used:

```cpp
const char VERTICAL = '|';
const char HORIZONTAL = '-';
const char CORNER = '+';
const char EMPTY = ' ';
const char SOLID = '#';
const char SLASH = '/';
const char BACKSLASH = '\\';
const char DOT = '.';
const char STAR = '*';
const char UNDERSCORE = '_';
const char CIRCLE = 'O';
```
