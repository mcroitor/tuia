#include "tuia.hpp"

using usm::graphics::TUIA;
using usm::graphics::Color;
using usm::graphics::Image;
using usm::graphics::Point;
using usm::graphics::BackgroundColor;

int main() {
    TUIA::Init();
    Image img {10, 10};

    for(int i = 0; i < img.GetWidth(); i++) {
        for(int j = 0; j < img.GetHeight(); j++) {
            img.SetColor({i, j}, Color(255, 255, 255));
        }
    }

    std::vector<BackgroundColor> colors = {
        BackgroundColor::Black,
        BackgroundColor::Red,
        BackgroundColor::Green,
        BackgroundColor::Yellow,
        BackgroundColor::Blue,
        BackgroundColor::Magenta,
        BackgroundColor::Cyan,
        BackgroundColor::White,
        BackgroundColor::BrightBlack,
        BackgroundColor::BrightRed,
        BackgroundColor::BrightGreen,
        BackgroundColor::BrightYellow,
        BackgroundColor::BrightBlue,
        BackgroundColor::BrightMagenta,
        BackgroundColor::BrightCyan,
        BackgroundColor::BrightWhite
    };

    for(int i = 0; i < img.GetWidth(); i++) {
        for(int j = 0; j < img.GetHeight(); j++) {
            auto colorIndex = rand() % colors.size();
            BackgroundColor bgColor = colors[colorIndex];
            Color color = usm::graphics::terminal::FromBackgroundColor(bgColor);
            img.SetColor({i, j}, color);
        }
    }
    TUIA::Draw({2, 2}, img);
    
    return 0;
}