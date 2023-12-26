#include "tuia.hpp"

using usm::graphics::TUIA;
using usm::graphics::Color;
using usm::graphics::Image;

int main() {
    TUIA::Init();
//    TUIA::SetBackgroundColor(usm::graphics::terminal::BackgroundColor::Black);
//    TUIA::ClearBlock({3, 3}, {10, 10});
//    TUIA::SetBackgroundColor(usm::graphics::terminal::BackgroundColor::Blue);
//    TUIA::ClearBlock({4, 4}, {6, 6});
//    TUIA::PutPoint({1, 1}, usm::graphics::terminal::BackgroundColor::BrightGreen);
//    TUIA::PutPoint({10, 3}, usm::graphics::terminal::BackgroundColor::Blue);
//    TUIA::PutPoint({11, 4}, usm::graphics::terminal::BackgroundColor::White);
    Image img {10, 10};

    img.SetColor({1, 2}, Color(255, 0, 0));
    img.SetColor({2, 2}, Color(170, 85, 0));
    img.SetColor({3, 2}, Color(0, 0, 170));
    TUIA::Draw({2, 2}, img);

    return 0;
}