#ifndef _USM_GRAPHICS_IMAGE_HPP_
#define _USM_GRAPHICS_IMAGE_HPP_

#include <cstdint>
#include <vector>
#include "color.hpp"
#include "point.hpp"

namespace usm::graphics
{
    class Image
    {
        std::vector<std::vector<Color> > lines;
    public:
        Image(uint32_t width, uint32_t height);
        Color GetColor(const Point& point) const;
        void SetColor(const Point& point, const Color& color);
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
    };
}
#endif