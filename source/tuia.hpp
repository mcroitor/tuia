#ifndef _USM_GRAPHICS_TUIA_HPP_
#define _USM_GRAPHICS_TUIA_HPP_

#include <cstdint>
#include <string>
#include "terminal_color.hpp"
#include "image.hpp"
#include "point.hpp"

namespace usm::graphics
{
    using terminal::BackgroundColor;
    using terminal::ForegroundColor;

    class TUIA
    {
        static ForegroundColor _foregroundColor;
        static BackgroundColor _backgroundColor;

        static std::string ColorCode();

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
}

#endif