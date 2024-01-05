#include "../source/tuia.hpp"

int main() {
    using usm::graphics::TUIA;
    using usm::graphics::Point;
    using usm::graphics::BackgroundColor;

    TUIA::Init();
    Point dim = TUIA::GetScreenSize();
    uint32_t width = dim.GetX();
    uint32_t height = dim.GetY();
    uint32_t SIZE = 7;
    BackgroundColor colors[SIZE] {
        BackgroundColor::Blue,
        BackgroundColor::Cyan,
        BackgroundColor::Gray,
        BackgroundColor::Green,
        BackgroundColor::Magenta,
        BackgroundColor::Red,
        BackgroundColor::Yellow,
    };
    for(uint32_t i = 0; i < SIZE; ++i) {
        TUIA::SetBackgroundColor(colors[i]);
        TUIA::ClearBlock({i + 1, i + 1}, {width - i - 1, height - i - 1});
        TUIA::WriteLine({i + 1, i + 1}, usm::graphics::terminal::FromBackgroundColor(colors[i]).ToString());
    }
    TUIA::SetCursor({0, height - 1});
    TUIA::ResetColors();
    return 0;
}