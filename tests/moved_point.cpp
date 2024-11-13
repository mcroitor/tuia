#include "tuia.hpp"

#include <thread>
#include <windows.h>

using usm::graphics::Point;
using usm::graphics::Image;
using usm::graphics::BackgroundColor;
using usm::graphics::ForegroundColor;
using usm::graphics::TUIA;

int main(){
    std::jthread stop([](){
        while (true)
        {
            auto qPressed = GetAsyncKeyState('Q');
            if (qPressed)
            {
                TUIA::ResetColors();
                exit(0);
            }
        }
        
    });

    TUIA::Init();
    TUIA::FullScreen();
    TUIA::ClearScreen();
    
    BackgroundColor pointColor = BackgroundColor::BrightRed;
    BackgroundColor imageColor = BackgroundColor::BrightBlack;
    int Width = 20;
    int Height = 10;
    Point p(0, 0);
    auto direction = std::make_pair(1, 1);
    Image image(Width, Height, imageColor);

    TUIA::WriteLine({0, Height + 2}, "Press `q` key to exit");

    while(true) {
        image.SetColor(p, pointColor);
        TUIA::Draw(image);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        // move point
        image.SetColor(p, imageColor);
        auto px = p.GetX() + direction.first;
        auto py = p.GetY() + direction.second;
        if (px < 0 || px >= Width) {
            direction.first = -direction.first;
            px = p.GetX() + direction.first;
        }
        if (py < 0 || py >= Height) {
            direction.second = -direction.second;
            py = p.GetY() + direction.second;
        }
        p = {px, py};
    }
    TUIA::ResetColors();
    std::cout << std::endl;
    return 0;
}
