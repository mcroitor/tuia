#include "../source/point.hpp"
#include "testframework.hpp"

using usm::graphics::Point;

bool test1() {
    std::cout << "[Point] default constructor" << std::endl;
    Point p;
    return (p.GetX() == 0 && p.GetY() == 0);
}

bool test2() {
    std::cout << "[Point] constructor with coordinates" << std::endl;
    Point p(3, 7);
    return (p.GetX() == 3 && p.GetY() == 7);
}

bool test3() {
    std::cout << "[Point] copy constructor" << std::endl;
    Point a(5, 9);
    Point b(a);
    return (b.GetX() == 5 && b.GetY() == 9);
}

bool test4() {
    std::cout << "[Point] assignment operator" << std::endl;
    Point a(2, 4);
    Point b;
    b = a;
    return (b.GetX() == 2 && b.GetY() == 4);
}

bool test5() {
    std::cout << "[Point] equality operator - equal points" << std::endl;
    Point a(1, 2);
    Point b(1, 2);
    return (a == b);
}

bool test6() {
    std::cout << "[Point] equality operator - different points" << std::endl;
    Point a(1, 2);
    Point b(3, 4);
    return !(a == b);
}

bool test7() {
    std::cout << "[Point] negative coordinates" << std::endl;
    Point p(-5, -10);
    return (p.GetX() == -5 && p.GetY() == -10);
}

int main() {
    usm::Test::Init();
    usm::Test::Unit(test1);
    usm::Test::Unit(test2);
    usm::Test::Unit(test3);
    usm::Test::Unit(test4);
    usm::Test::Unit(test5);
    usm::Test::Unit(test6);
    usm::Test::Unit(test7);
    usm::Test::Result();
    return 0;
}
