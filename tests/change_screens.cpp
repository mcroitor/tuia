#include "tuia.hpp"

#include <vector>

using usm::graphics::Point;
using usm::graphics::Color;
using usm::graphics::BackgroundColor;
using usm::graphics::ForegroundColor;
using usm::graphics::terminal::FromBackgroundColor;
using usm::graphics::Image;
using usm::graphics::TUIA;

int main() {
    TUIA::Init();

    std::vector<Image> images(20, Image(20, 80, BackgroundColor::BrightBlack));

    for(int i = 0; i < images.size(); ++i){
        images[i].SetColor({(uint32_t)i, (uint32_t)i}, Color(255, 255, 255));
    }

    for(int i = 0; i < images.size(); ++i){
        TUIA::Draw({1, 1}, images[i]);
    }
    TUIA::ResetColors();

    return 0;
}