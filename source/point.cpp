#include "point.hpp"

namespace usm::graphics
{
    Point::Point(uint32_t x, uint32_t y): _x(x), _y(y) {}
    
    Point::Point(const Point &point): _x(point.GetX()), _y(point.GetY()) {}
    
    uint32_t Point::GetX() const { return _x; }
    
    uint32_t Point::GetY() const { return _y; }
    
    Point Point::operator=(const Point &point) {
        _x = point.GetX();
        _y = point.GetY();
        return *this;
    }
    
    bool Point::operator==(const Point &point) const {
        return _x == point.GetX() && _y == point.GetY();
    }

}