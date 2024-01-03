#ifndef _USM_GRAPHICS_TERMINAL_COLOR_HPP_
#define _USM_GRAPHICS_TERMINAL_COLOR_HPP_

#include "color.hpp"

namespace usm::graphics::terminal
{
    using usm::graphics::Color;
    
    /**
     * @brief names and ASCII codes for foreground color
    */
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

    /**
     * @brief names and ASCII codes for background color
    */
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

    /**
     * @brief Convert ForegroundColor to Color
     * @param color Foreground Color
     * @return Color
     */
    Color FromForegroundColor(ForegroundColor color);
    /**
     * @brief Convert BackgroundColor to Color
     * @param color Background Color
     * @return Color
     */
    Color FromBackgroundColor(BackgroundColor color);
    /**
     * @brief Convert Color to ForegroundColor
     * @param color RGB Color
     * @return ForegroundColor
     */
    ForegroundColor ToForegroundColor(const Color &color);
    /**
     * @brief Convert Color to BackgroundColor
     * @param color RGB Color
     * @return BackgroundColor
     */
    BackgroundColor ToBackgroundColor(const Color &color);
}

#endif