#ifndef _USM_GRAPHICS_TERMINAL_BACKGROUND_COLOR_HPP_
#define _USM_GRAPHICS_TERMINAL_BACKGROUND_COLOR_HPP_

#include "color.hpp"

namespace usm::graphics::terminal
{
    using usm::graphics::Color;
    
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
     * @brief Convert BackgroundColor to Color
     * @param color BackgroundColor
     * @return RGB Color
     */
    Color FromBackgroundColor(BackgroundColor color);

    /**
     * @brief Convert Color to BackgroundColor
     * @param color RGB Color
     * @return BackgroundColor
     */
    BackgroundColor ToBackgroundColor(const Color &color);
}

#endif // _USM_GRAPHICS_TERMINAL_BACKGROUND_COLOR_HPP_