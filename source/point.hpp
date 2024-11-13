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
        int _x;
        int _y;

    public:
        /**
         * @brief Create a Point object from coordinates
         */
        Point(int x = 0, int y = 0);
        /**
         * @brief Copy constructor
         */
        Point(const Point& point);
        /**
         * @brief get X value
         * @return int
         */
        int GetX() const;

        /**
         * @brief get y value
         * @return int
         */
        int GetY() const;

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