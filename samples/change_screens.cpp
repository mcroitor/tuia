#include "tuia.hpp"

#include <vector>
#include <thread>

using usm::graphics::Point;
using usm::graphics::Color;
using usm::graphics::BackgroundColor;
using usm::graphics::ForegroundColor;
using usm::graphics::terminal::FromBackgroundColor;
using usm::graphics::Image;
using usm::graphics::TUIA;

int main() {
    TUIA::Init();
    TUIA::SetBackgroundColor(usm::graphics::terminal::BackgroundColor::Black);
    TUIA::ClearScreen();

    std::vector<Image> images(20, Image(40, 20, BackgroundColor::BrightBlack));

    for(int i = 0; i < images.size(); ++i){
        images[i].SetColor({i, i}, Color(255, 255, 255));
    }
    for(int i = 0; i < images.size(); ++i){
        TUIA::Draw(images[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}