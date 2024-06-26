#include "tuia.hpp"

using usm::graphics::Color;
using usm::graphics::TUIA;

int main()
{
    TUIA::Init();

    std::vector<Color> colors{
        Color(0, 0, 170),
        Color(0, 170, 0),
        Color(170, 0, 0),
        Color(170, 85, 0),
        Color(170, 0, 170),
        Color(170, 170, 0),
        Color(0, 170, 170),
        Color(170, 170, 170),
        Color(85, 85, 85),
        Color(85, 85, 255),
        Color(255, 85, 85),
        Color(85, 255, 85),
        Color(255, 255, 85),
        Color(255, 85, 255),
        Color(85, 255, 255),
        Color(255, 255, 255)};

    for (int i = 0; i < colors.size(); ++i)
    {
        TUIA::SetBackgroundColor(colors[i]);
        if (colors[i] == Color(0, 0, 0))
        {
            TUIA::SetForegroundColor(Color(255, 255, 255));
        }
        else
        {
            TUIA::SetForegroundColor(Color(0, 0, 0));
        }
        TUIA::WriteLine({1, (uint32_t)i}, colors[i].ToString());
    }

    return 0;
}