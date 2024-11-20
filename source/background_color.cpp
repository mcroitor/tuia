#include <map>
#include <cmath>
#include "background_color.hpp"

namespace usm::graphics::terminal
{
    Color FromBackgroundColor(BackgroundColor color)
    {
        const std::map<BackgroundColor, Color> map{
            {BackgroundColor::Black, Color{0, 0, 0}},
            {BackgroundColor::Red, Color{170, 0, 0}},
            {BackgroundColor::Green, Color{0, 170, 0}},
            {BackgroundColor::Yellow, Color{170, 85, 0}},
            {BackgroundColor::Blue, Color{0, 0, 170}},
            {BackgroundColor::Magenta, Color{170, 0, 170}},
            {BackgroundColor::Cyan, Color{0, 170, 170}},
            {BackgroundColor::White, Color{170, 170, 170}},
            {BackgroundColor::Gray, Color{85, 85, 85}},
            {BackgroundColor::BrightRed, Color{255, 85, 85}},
            {BackgroundColor::BrightGreen, Color{85, 255, 85}},
            {BackgroundColor::BrightYellow, Color{255, 255, 85}},
            {BackgroundColor::BrightBlue, Color{85, 85, 255}},
            {BackgroundColor::BrightMagenta, Color{255, 85, 255}},
            {BackgroundColor::BrightCyan, Color{85, 255, 255}},
            {BackgroundColor::BrightWhite, Color{255, 255, 255}},
        };
        return map.at(color);
    }

    BackgroundColor ToBackgroundColor(const Color &color)
    {
        const std::map<Color, BackgroundColor> map{
            {Color{0, 0, 0}, BackgroundColor::Black},
            {Color{170, 0, 0}, BackgroundColor::Red},
            {Color{0, 170, 0}, BackgroundColor::Green},
            {Color{170, 85, 0}, BackgroundColor::Yellow},
            {Color{0, 0, 170}, BackgroundColor::Blue},
            {Color{170, 0, 170}, BackgroundColor::Magenta},
            {Color{0, 170, 170}, BackgroundColor::Cyan},
            {Color{170, 170, 170}, BackgroundColor::White},
            {Color{85, 85, 85}, BackgroundColor::Gray},
            {Color{255, 85, 85}, BackgroundColor::BrightRed},
            {Color{85, 255, 85}, BackgroundColor::BrightGreen},
            {Color{255, 255, 85}, BackgroundColor::BrightYellow},
            {Color{85, 85, 255}, BackgroundColor::BrightBlue},
            {Color{255, 85, 255}, BackgroundColor::BrightMagenta},
            {Color{85, 255, 255}, BackgroundColor::BrightCyan},
            {Color{255, 255, 255}, BackgroundColor::BrightWhite},
        };
        Color terminal = color.ToTerminal();
        if (map.count(terminal) > 0)
        {
            return map.at(terminal);
        }
        return terminal::BackgroundColor::Black;
    }
}