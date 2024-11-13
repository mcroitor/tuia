#include "point.hpp"

namespace usm::graphics
{
    Point::Point(int x, int y): _x(x), _y(y) {}
    
    Point::Point(const Point &point): _x(point.X()), _y(point.Y()) {}

    int Point::GetX() const { return _x; }
    
    int Point::GetY() const { return _y; }
    
    Point Point::operator=(const Point &point) {
        _x = point.X();
        _y = point.Y();
        return *this;
    }
    
    bool Point::operator==(const Point &point) const {
        return _x == point.X() && _y == point.Y();
    }

}