#include "../source/text_image.hpp"
#include "testframework.hpp"

using usm::graphics::Point;
using usm::graphics::terminal::TextImage;

bool test1() {
    std::cout << "[TextImage] constructor dimensions" << std::endl;
    TextImage img(8, 4);
    return (img.GetWidth() == 8 && img.GetHeight() == 4);
}

bool test2() {
    std::cout << "[TextImage] default fill symbol" << std::endl;
    TextImage img(5, 5, ' ');
    return (img.GetSymbol({2, 2}) == ' ');
}

bool test3() {
    std::cout << "[TextImage] constructor with fill symbol" << std::endl;
    TextImage img(3, 3, '#');
    return (img.GetSymbol({0, 0}) == '#' && img.GetSymbol({2, 2}) == '#');
}

bool test4() {
    std::cout << "[TextImage] SetSymbol / GetSymbol roundtrip" << std::endl;
    TextImage img(5, 5);
    img.SetSymbol({3, 1}, 'X');
    return (img.GetSymbol({3, 1}) == 'X');
}

bool test5() {
    std::cout << "[TextImage] Fill overwrites all symbols" << std::endl;
    TextImage img(4, 4, ' ');
    img.SetSymbol({1, 1}, 'A');
    img.Fill('*');
    return (img.GetSymbol({1, 1}) == '*' && img.GetSymbol({0, 0}) == '*');
}

bool test6() {
    std::cout << "[TextImage] Clear resets to spaces" << std::endl;
    TextImage img(4, 4, '#');
    img.Clear();
    return (img.GetSymbol({0, 0}) == ' ' && img.GetSymbol({3, 3}) == ' ');
}

bool test7() {
    std::cout << "[TextImage] In() - inside bounds" << std::endl;
    TextImage img(6, 4);
    return img.In({0, 0}) && img.In({5, 3});
}

bool test8() {
    std::cout << "[TextImage] In() - outside bounds" << std::endl;
    TextImage img(3, 3);
    return !img.In({3, 0}) && !img.In({0, 3}) && !img.In({-1, 0});
}

bool test9() {
    std::cout << "[TextImage] copy constructor" << std::endl;
    TextImage a(3, 3, 'A');
    TextImage b(a);
    b.SetSymbol({0, 0}, 'B');
    return (a.GetSymbol({0, 0}) == 'A' && b.GetSymbol({0, 0}) == 'B');
}

bool test10() {
    std::cout << "[TextImage] move constructor" << std::endl;
    TextImage a(4, 4, 'M');
    TextImage b(std::move(a));
    return (b.GetWidth() == 4 && b.GetHeight() == 4 && b.GetSymbol({0, 0}) == 'M');
}

bool test11() {
    std::cout << "[TextImage] move assignment operator" << std::endl;
    TextImage a(3, 2, 'Q');
    TextImage b(1, 1);
    b = std::move(a);
    return (b.GetWidth() == 3 && b.GetHeight() == 2 && b.GetSymbol({1, 1}) == 'Q');
}

bool test12() {
    std::cout << "[TextImage] SetPart / GetPart roundtrip" << std::endl;
    TextImage canvas(10, 10, '.');
    TextImage patch(3, 3, 'X');
    canvas.SetPart({2, 2}, patch);
    TextImage extracted = canvas.GetPart({2, 2}, {5, 5});
    return (extracted.GetSymbol({0, 0}) == 'X' && extracted.GetSymbol({2, 2}) == 'X');
}

bool test13() {
    std::cout << "[TextImage] Clone produces independent copy" << std::endl;
    TextImage a(3, 3, 'A');
    TextImage b = a.Clone();
    b.SetSymbol({1, 1}, 'Z');
    return (a.GetSymbol({1, 1}) == 'A' && b.GetSymbol({1, 1}) == 'Z');
}

bool test14() {
    std::cout << "[TextImage] Save and Load roundtrip" << std::endl;
    TextImage img(5, 3, '-');
    img.SetSymbol({2, 1}, 'T');
    img.Save("test_textimage_tmp.txt");

    TextImage loaded(1, 1);
    loaded.Load("test_textimage_tmp.txt");
    return (loaded.GetWidth() == 5 &&
            loaded.GetHeight() == 3 &&
            loaded.GetSymbol({2, 1}) == 'T');
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
    usm::Test::Result();
    return 0;
}
