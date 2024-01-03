#ifndef _USM_GRAPHICS_POINT_HPP_
#define _USM_GRAPHICS_POINT_HPP_

#include <cstdint>

namespace usm::graphics
{
    /**
     * @brief Simple Point representation
     */
    class Point
    {
        uint32_t _x;
        uint32_t _y;

    public:
        /**
         * @brief Create a Point object from coordinates
         */
        Point(uint32_t x = 0, uint32_t y = 0);
        /**
         * @brief Copy constructor
         */
        Point(const Point& point);
        /**
         * @brief get X value
         * @return uint32_t
         */
        uint32_t GetX() const;
        /**
         * @brief get y value
         * @return uint32_t
         */
        uint32_t GetY() const;
        /**
         * @brief copy operator
         * @param point left value object
         * @return Point
         */
        Point operator = (const Point& point);
        /**
         * @brief equal operator
         * @param point left value object
         * @return bool
        */
        bool operator == (const Point& point) const;
    };
}

#endif