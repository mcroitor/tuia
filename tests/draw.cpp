#include "tuia.hpp"

using usm::graphics::TUIA;
using usm::graphics::Color;
using usm::graphics::Image;

int main() {
    TUIA::Init();

    Image img {10, 10};

    img.SetColor({2, 2}, Color(170, 85, 0));
    img.SetColor({3, 2}, Color(0, 0, 170));
    img.SetColor({4, 2}, Color(255, 0, 0));

    img.DrawLine({1, 1}, {1, 8}, Color(255, 255, 255));
    img.DrawLine({1, 8}, {8, 8}, Color(255, 255, 255));
    img.DrawLine({8, 8}, {8, 1}, Color(255, 255, 255));
    img.DrawLine({8, 1}, {1, 1}, Color(255, 255, 255));

    img.Save("image.txt");

    TUIA::Draw({2, 2}, img);

    return 0;
}