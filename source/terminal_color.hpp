#ifndef _USM_GRAPHICS_TERMINAL_COLOR_HPP_
#define _USM_GRAPHICS_TERMINAL_COLOR_HPP_

#include "color.hpp"

namespace usm::graphics::terminal
{
    using usm::graphics::Color;
    
    enum class ForegroundColor
    {
        Black = 30,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        BrightBlack = 90,
        Gray = 90,
        BrightRed,
        BrightGreen,
        BrightYellow,
        BrightBlue,
        BrightMagenta,
        BrightCyan,
        BrightWhite,
    };

    enum class BackgroundColor
    {
        Black = 40,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        BrightBlack = 100,
        Gray = 100,
        BrightRed,
        BrightGreen,
        BrightYellow,
        BrightBlue,
        BrightMagenta,
        BrightCyan,
        BrightWhite,
    };

    Color FromForegroundColor(ForegroundColor color);
    Color FromBackgroundColor(BackgroundColor color);
    ForegroundColor ToForegroundColor(const Color &color);
    BackgroundColor ToBackgroundColor(const Color &color);
}

#endif