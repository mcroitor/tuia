#include <map>
#include <cmath>
#include "foreground_color.hpp"

namespace usm::graphics::terminal
{
    Color FromForegroundColor(ForegroundColor color)
    {
        const std::map<ForegroundColor, Color> map{
            {ForegroundColor::Black, Color{0, 0, 0}},
            {ForegroundColor::Red, Color{170, 0, 0}},
            {ForegroundColor::Green, Color{0, 170, 0}},
            {ForegroundColor::Yellow, Color{170, 85, 0}},
            {ForegroundColor::Blue, Color{0, 0, 170}},
            {ForegroundColor::Magenta, Color{170, 0, 170}},
            {ForegroundColor::Cyan, Color{0, 170, 170}},
            {ForegroundColor::White, Color{170, 170, 170}},
            {ForegroundColor::Gray, Color{85, 85, 85}},
            {ForegroundColor::BrightRed, Color{255, 85, 85}},
            {ForegroundColor::BrightGreen, Color{85, 255, 85}},
            {ForegroundColor::BrightYellow, Color{255, 255, 85}},
            {ForegroundColor::BrightBlue, Color{85, 85, 255}},
            {ForegroundColor::BrightMagenta, Color{255, 85, 255}},
            {ForegroundColor::BrightCyan, Color{85, 255, 255}},
            {ForegroundColor::BrightWhite, Color{255, 255, 255}},
        };
        return map.at(color);
    }

    ForegroundColor ToForegroundColor(const Color &color)
    {
        const std::map<Color, ForegroundColor> map {
            {Color{0, 0, 0}, ForegroundColor::Black},
            {Color{170, 0, 0}, ForegroundColor::Red},
            {Color{0, 170, 0}, ForegroundColor::Green},
            {Color{170, 85, 0}, ForegroundColor::Yellow},
            {Color{0, 0, 170}, ForegroundColor::Blue},
            {Color{170, 0, 170}, ForegroundColor::Magenta},
            {Color{0, 170, 170}, ForegroundColor::Cyan},
            {Color{170, 170, 170}, ForegroundColor::White},
            {Color{85, 85, 85}, ForegroundColor::Gray},
            {Color{255, 85, 85}, ForegroundColor::BrightRed},
            {Color{85, 255, 85}, ForegroundColor::BrightGreen},
            {Color{255, 255, 85}, ForegroundColor::BrightYellow},
            {Color{85, 85, 255}, ForegroundColor::BrightBlue},
            {Color{255, 85, 255}, ForegroundColor::BrightMagenta},
            {Color{85, 255, 255}, ForegroundColor::BrightCyan},
            {Color{255, 255, 255}, ForegroundColor::BrightWhite},
        };
        Color terminal = color.ToTerminal();
        if (map.count(terminal) > 0)
        {
            return map.at(terminal);
        }
        return terminal::ForegroundColor::White;
    }
}