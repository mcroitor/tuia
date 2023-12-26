#include <map>
#include <cmath>
#include "terminal_color.hpp"

namespace usm::graphics::terminal
{
    Color FromForegroundColor(ForegroundColor color)
    {
        std::map<ForegroundColor, Color> map{
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
        return map[color];
    }

    Color FromBackgroundColor(BackgroundColor color)
    {
        std::map<BackgroundColor, Color> map{
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
        return map[color];
    }
    ForegroundColor ToForegroundColor(const Color &color)
    {
        Color terminal = color.ToTerminal();
        return terminal::ForegroundColor::White;
    }

    BackgroundColor ToBackgroundColor(const Color &color)
    {
        Color terminal = color.ToTerminal();
        return terminal::BackgroundColor::White;
    }
}