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
    uint32_t width = dim.GetX();
    uint32_t height = dim.GetY();
    std::deque<BackgroundColor> colors{
        BackgroundColor::Blue,
        BackgroundColor::Cyan,
        BackgroundColor::Gray,
        BackgroundColor::Green,
        BackgroundColor::Magenta,
        BackgroundColor::Red,
        BackgroundColor::Yellow,
    };
    int rounds = 3;
    while (rounds > 0)
    {
        for (uint32_t i = 0; i < colors.size(); ++i)
        {
            TUIA::SetBackgroundColor(colors[i]);
            TUIA::ClearBlock({(int)i + 1, (int)i + 1}, {(int)(width - i - 1), (int)(height - i - 1)});
            TUIA::WriteLine({(int)i + 1, (int)i + 1}, usm::graphics::terminal::FromBackgroundColor(colors[i]).ToString());
            sleep_for(milliseconds(300));
        }
        TUIA::SetCursor({0, (int)height - 1});
        TUIA::ResetColors();
        auto color = colors.front();
        colors.pop_front();
        colors.push_back(color);
        --rounds;
    }
    TUIA::ResetColors();
    return 0;
}