#include "point.hpp"

namespace usm::graphics
{
    Point::Point(uint32_t x, uint32_t y): _x(x), _y(y) {}
    
    Point::Point(const Point &point): _x(point.X()), _y(point.Y()) {}
    
    uint32_t Point::X() const { return _x; }
    
    uint32_t Point::Y() const { return _y; }
    
    Point Point::operator=(const Point &point) {
        _x = point.X();
        _y = point.Y();
        return *this;
    }
    
    bool Point::operator==(const Point &point) const {
        return _x == point.X() && _y == point.Y();
    }

}