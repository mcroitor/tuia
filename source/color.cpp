#include <iomanip>
#include <cmath>
#include "color.hpp"

namespace usm::graphics
{
    uint32_t Color::ExtractRed(uint32_t color)
    {
        return (color & 0x00FF0000) >> 16;
    }

    uint32_t Color::ExtractGreen(uint32_t color)
    {
        return (color & 0x0000FF00) >> 8;
    }

    uint32_t Color::ExtractBlue(uint32_t color)
    {
        return (color & 0x000000FF);
    }

    Color::Color() : _value(0) {}

    Color::Color(uint32_t value) : _value(value) {}

    Color::Color(const Color &color) : _value(color.Value()) {}

    Color::Color(uint8_t red, uint8_t green, uint8_t blue) : 
        _value(((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue)
    {
    }

    Color Color::operator=(const Color &color)
    {
        _value = color.Value();
        return *this;
    }

    bool Color::operator==(const Color &color) const
    {
        return (_value == color.Value());
    }

    uint32_t Color::Red() const
    {
        return Color::ExtractRed(_value);
    }

    uint32_t Color::Green() const
    {
        return Color::ExtractGreen(_value);
    }
    
    uint32_t Color::Blue() const
    {
        return Color::ExtractBlue(_value);
    }

    uint32_t Color::Value() const
    {
        return _value;
    }

    Color Color::ToTerminal() const {
        uint8_t red = static_cast<uint8_t>(std::round(Red() / 85.0f) * 85);
        uint8_t green = static_cast<uint8_t>(std::round(Green() / 85.0f) * 85);
        uint8_t blue = static_cast<uint8_t>(std::round(Blue() / 85.0f) * 85);

        return Color {red, green, blue};
    }

    std::istream &operator>>(std::istream &in, Color &color)
    {
        int tmp;
        in >> tmp;
        color = Color(tmp);
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const Color &color)
    {
        out << "0x00" << std::hex 
            << std::setw(2) << std::setfill('0') << static_cast<int>(color.Red())
            << std::setw(2) << std::setfill('0') << static_cast<int>(color.Green())
            << std::setw(2) << std::setfill('0') << static_cast<int>(color.Blue());
        out << std::dec;
        return out;
    }

    int operator <=> (const Color& left, const Color& right) {
        if (left.Value() < right.Value()) {
            return -1;
        }
        if (left.Value() > right.Value()) {
            return 1;
        }
        return 0;
    }
}
