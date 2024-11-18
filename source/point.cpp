#include "point.hpp"

namespace usm::graphics
{
    Point::Point(int x, int y): _x(x), _y(y) {}
    
    Point::Point(const Point &point): _x(point.GetX()), _y(point.GetY()) {}

    int Point::GetX() const { return _x; }
    
    int Point::GetY() const { return _y; }
    
    Point Point::operator=(const Point &point) {
        _x = point.GetX();
        _y = point.GetY();
        return *this;
    }
    
    bool Point::operator==(const Point &point) const {
        return _x == point.GetX() && _y == point.GetY();
    }

}