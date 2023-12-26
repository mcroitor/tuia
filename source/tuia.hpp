#ifndef _USM_GRAPHICS_TUIA_HPP_
#define _USM_GRAPHICS_TUIA_HPP_

#include <cstdint>
#include <string>
#include "color.hpp"
#include "image.hpp"
#include "point.hpp"

namespace usm::graphics
{

    class TUIA {
        static terminal::ForegroundColor _foregroundColor;
        static terminal::BackgroundColor _backgroundColor;
    public:
        void SetForegroundColor(const Color& foregroundColor);
        void SetBackgroundColor(const Color& backgroundColor);
        void SetForegroundColor(const terminal::ForegroundColor& foregroundColor);
        void SetBackgroundColor(const terminal::BackgroundColor& backgroundColor);
        Color GetForegroundColor() const;
        Color GetBackgroundColor() const;
        void WriteLine(const Point& position, const std::string& line) const;
        void ClearLine(const Point& position, uint32_t nChars) const;
        void ClearBlock(const Point& leftTop, const Point& rightBottom) const;
        void ClearBlock(const Point& position, uint32_t nChars, uint32_t nLines) const;
        void ClearScreen() const;
        void Draw(const Point& position, const Image& image) const;
        void SetCursor(const Point& position) const;
        Point GetScreenSize() const;
    };
}

#endif