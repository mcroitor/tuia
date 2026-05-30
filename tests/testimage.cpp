#include "../source/image.hpp"
#include "testframework.hpp"

using usm::graphics::Image;
using usm::graphics::Point;
using usm::graphics::Color;
using usm::graphics::terminal::BackgroundColor;

bool test1() {
    std::cout << "[Image] constructor dimensions" << std::endl;
    Image img(10, 5);
    return (img.GetWidth() == 10 && img.GetHeight() == 5);
}

bool test2() {
    std::cout << "[Image] zero height - GetWidth() safe" << std::endl;
    Image img(8, 0);
    return (img.GetWidth() == 0 && img.GetHeight() == 0);
}

bool test3() {
    std::cout << "[Image] zero width - GetHeight() safe" << std::endl;
    Image img(0, 5);
    return (img.GetHeight() == 5);
}

bool test4() {
    std::cout << "[Image] default fill color" << std::endl;
    Image img(4, 4, BackgroundColor::Red);
    return (img.GetColor({1, 1}) == BackgroundColor::Red);
}

bool test5() {
    std::cout << "[Image] SetColor / GetColor roundtrip" << std::endl;
    Image img(5, 5);
    img.SetColor({2, 3}, BackgroundColor::Green);
    return (img.GetColor({2, 3}) == BackgroundColor::Green);
}

bool test6() {
    std::cout << "[Image] SetSymbol / GetSymbol roundtrip" << std::endl;
    Image img(5, 5);
    img.SetSymbol({1, 1}, 'A');
    return (img.GetSymbol({1, 1}) == 'A');
}

bool test7() {
    std::cout << "[Image] In() - point inside bounds" << std::endl;
    Image img(10, 10);
    return img.In({5, 5});
}

bool test8() {
    std::cout << "[Image] In() - point outside bounds" << std::endl;
    Image img(5, 5);
    return !img.In({5, 5}) && !img.In({-1, 0}) && !img.In({0, -1});
}

bool test9() {
    std::cout << "[Image] SetColor out of bounds - no crash" << std::endl;
    Image img(3, 3);
    img.SetColor({10, 10}, BackgroundColor::Blue);
    return true; // must not crash
}

bool test10() {
    std::cout << "[Image] GetColor out of bounds returns Black" << std::endl;
    Image img(3, 3);
    return (img.GetColor({99, 99}) == BackgroundColor::Black);
}

bool test11() {
    std::cout << "[Image] Clone produces independent copy" << std::endl;
    Image img(4, 4, BackgroundColor::Blue);
    Image copy = img.Clone();
    copy.SetColor({0, 0}, BackgroundColor::Red);
    return (img.GetColor({0, 0}) == BackgroundColor::Blue &&
            copy.GetColor({0, 0}) == BackgroundColor::Red);
}

bool test12() {
    std::cout << "[Image] DrawLine horizontal - endpoints set" << std::endl;
    Image img(10, 10);
    img.DrawLine({1, 5}, {8, 5}, Color(0x00FF00));
    // All pixels on the line should be set (not Black)
    bool ok = true;
    for (int x = 1; x <= 8; ++x) {
        if (img.GetColor({x, 5}) == BackgroundColor::Black) { ok = false; break; }
    }
    return ok;
}

bool test13() {
    std::cout << "[Image] DrawLine single point (start == end)" << std::endl;
    Image img(5, 5);
    img.DrawLine({2, 2}, {2, 2}, Color(0xFF0000));
    return (img.GetColor({2, 2}) != BackgroundColor::Black);
}

bool test14() {
    std::cout << "[Image] Save and Load roundtrip" << std::endl;
    Image img(4, 3, BackgroundColor::Yellow);
    img.SetSymbol({1, 1}, 'Z');
    img.Save("test_image_tmp.txt");

    Image loaded(1, 1);
    loaded.Load("test_image_tmp.txt");
    return (loaded.GetWidth() == 4 &&
            loaded.GetHeight() == 3 &&
            loaded.GetColor({0, 0}) == BackgroundColor::Yellow &&
            loaded.GetSymbol({1, 1}) == 'Z');
}

bool test15() {
    std::cout << "[Image] Load non-existent file - no crash" << std::endl;
    Image img(2, 2);
    img.Load("nonexistent_file_xyz.txt");
    return true; // must not crash
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
    usm::Test::Unit(test10);
    usm::Test::Unit(test11);
    usm::Test::Unit(test12);
    usm::Test::Unit(test13);
    usm::Test::Unit(test14);
    usm::Test::Unit(test15);
    usm::Test::Result();
    return 0;
}
