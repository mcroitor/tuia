#include "../source/color.hpp"
#include "testframework.hpp"

using usm::graphics::Color;

void validate(bool expression, std::string pass = "pass", std::string fail = "fail") {
    std::cout << (expression ? pass : fail) << std::endl;
}

bool test1() {
    std::cout << "[Color] default constructor" << std::endl;
    Color color;
    return (color.Value() == 0);
}

bool test2() {
    std::cout << "[Color] constructor with 1 parameter" << std::endl;
    int greenColor = 0x00ff00;
    Color color(greenColor);
    return (color.Value() == greenColor);
}

bool test3() {
    std::cout << "[Color] constructor with 3 parameters" << std::endl;
    uint8_t red = 255;
    uint8_t green = 0;
    uint8_t blue = 0;
    Color color(red, green, blue);
    std::cout << color << std::endl;
    return (color.Value() == 0xff0000);
}

bool test4() {
    std::cout << "[Color] extract red" << std::endl;
    uint32_t color = 0xA23456;
    uint8_t red = 0xA2;
    return (Color::ExtractRed(color) == red);
}

bool test5() {
    std::cout << "[Color] extract green" << std::endl;
    uint32_t color = 0xA23456;
    uint8_t green = 0x34;
    return (Color::ExtractGreen(color) == green);
}

bool test6() {
    std::cout << "[Color] extract blue" << std::endl;
    uint32_t color = 0xA23456;
    uint8_t blue = 0x56;
    return (Color::ExtractBlue(color) == blue);
}

bool test7() {
    std::cout << "[Color] get red channel" << std::endl;
    uint32_t color = 0xA23456;
    Color c {color};
    return (c.Red() == 0xA2);
}

bool test8() {
    std::cout << "[Color] get green channel" << std::endl;
    uint32_t color = 0xA23456;
    Color c {color};
    return (c.Green() == 0x34);
}

bool test9() {
    std::cout << "[Color] get blue channel" << std::endl;
    uint32_t color = 0xA23456;
    Color c {color};
    return (c.Blue() == 0x56);
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
    usm::Test::Unit(test8);
    usm::Test::Unit(test9);

    usm::Test::Result();

    return 0;
}