#ifndef _USM_GRAPHICS_POINT_HPP_
#define _USM_GRAPHICS_POINT_HPP_

#include <cstdint>

namespace usm::graphics
{
    class Point
    {
        uint32_t _x;
        uint32_t _y;

    public:
        Point();
        Point(uint32_t x, uint32_t y);
        Point(const Point& point);
        uint32_t GetX() const;
        uint32_t GetY() const;
        Point operator = (const Point& point);
        bool operator == (const Point& point) const;
    };
}

#endif