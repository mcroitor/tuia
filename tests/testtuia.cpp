#include "tuia.hpp"
#include "testframework.hpp"

using usm::graphics::TUIA;

bool test1() {
    std::cout << "[TUIA] window size" << std::endl;
    usm::graphics::Point point = TUIA::GetScreenSize();
    std::cout << "screen width = " << point.GetX() << std::endl;
    std::cout << "screen height = " << point.GetY() << std::endl;
    return true;
}

bool test2() {
    std::cout << "[TUIA] cursor position" << std::endl;
    usm::graphics::Point point = TUIA::GetCursor();
    std::cout << "cursor x = " << point.GetX() << std::endl;
    std::cout << "cursor y = " << point.GetY() << std::endl;
    return true;
}

int main() {
    usm::Test::Init();

    usm::Test::Unit(test1);
    usm::Test::Unit(test2);

    usm::Test::Result();

    return 0;
}