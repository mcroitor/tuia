#include <deque>
#include <thread>
#include <chrono>
#include "../source/tuia.hpp"

int main()
{
    using usm::graphics::BackgroundColor;
    using usm::graphics::Point;
    using usm::graphics::TUIA;

    using std::chrono::milliseconds;
    using std::this_thread::sleep_for;

    TUIA::Init();
    Point dim = TUIA::GetScreenSize();
    uint32_t width = dim.X();
    uint32_t height = dim.Y();
    std::deque<BackgroundColor> colors{
        BackgroundColor::Blue,
        BackgroundColor::Cyan,
        BackgroundColor::Gray,
        BackgroundColor::Green,
        BackgroundColor::Magenta,
        BackgroundColor::Red,
        BackgroundColor::Yellow,
    };
    /*
    int oops = 0;
    while (oops > 0)
    {
        for (uint32_t i = 0; i < colors.size(); ++i)
        {
            TUIA::SetBackgroundColor(colors[i]);
            TUIA::ClearBlock({i + 1, i + 1}, {width - i - 1, height - i - 1});
            TUIA::WriteLine({i + 1, i + 1}, usm::graphics::terminal::FromBackgroundColor(colors[i]).ToString());
        }
        TUIA::SetCursor({0, height - 1});
        TUIA::ResetColors();
        auto color = colors.front();
        colors.pop_front();
        colors.push_back(color);
        // sleep_for(milliseconds(1000));
        system("pause");
        --oops;
    }
    */
    sleep_for(milliseconds(1000));
    TUIA::SetBackgroundColor(colors[0]);
    TUIA::ClearScreen();
    sleep_for(milliseconds(1000));
    TUIA::SetBackgroundColor(colors[1]);
    TUIA::ClearScreen();
    sleep_for(milliseconds(1000));
    //TUIA::Init();
    return 0;
}