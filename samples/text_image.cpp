#include "../source/tuia.hpp"

#include <thread>

using usm::graphics::Point;
using usm::graphics::TUIA;
using usm::graphics::terminal::TextImage;

void SetCar(TextImage &textImage, const Point &position)
{
    std::string car[16] = {
        "                   __..-======-------..__                             ",
        "              . '    ______    ___________`.                          ",
        "            .' .--. '.-----.`. `.-----.-----\\                         ",
        "           / .'   | ||      `.`\\\\     \\     \\\\            _           ",
        "         .' /     | ||        \\ \\\\_____\\_____\\\\__________[_]          ",
        "        /   `-----' |'---------`\\  .'                       \\         ",
        "       /============|============\\'-------------------.._____|        ",
        "    .-`---.         |-==.        |'.__________________  =====|-._     ",
        "  .'        `.      |            |      .--------.    _` ====|  _ .   ",
        " /     __     \\     |            |   .'           `. [_] `.==| [_] \\  ",
        "[   .`    `.  |     |            | .'     .---.     \\      \\=|     |  ",
        "|  | / .-. '  |_____\\___________/_/     .'---. `.    |     | |     |  ",
        " `-'| | O |'..`------------------'.....'/ .-. \\ |    |       ___.--'  ",
        "     \\ `-' / /   `._.'                 | | O | |'___...----''___.--'  ",
        "      `._.'.'                           \\ `-' / [___...----''_.'      ",
        "                                         `._.'.'                      ",
    };

    for (int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 70; j++)
        {
            textImage.SetSymbol({position.GetX() + j, position.GetY() + i}, car[i][j]);
        }
    }
}

int main()
{

    TUIA::Init();
    TUIA::ClearScreen();
    TUIA::FullScreen();
    // auto screenSize = TUIA::GetScreenSize();
    TextImage textImage(130, 32);

    for (int i = 0; i < textImage.GetWidth(); i++)
    {
        textImage.SetSymbol({i, 0}, '-');
        textImage.SetSymbol({i, textImage.GetHeight() - 1}, '-');
    }

    for (int i = 0; i < textImage.GetHeight(); i++)
    {
        textImage.SetSymbol({0, i}, '|');
        textImage.SetSymbol({textImage.GetWidth() - 1, i}, '|');
    }

    std::vector<TextImage> slides(50, textImage);

    for (int i = 0; i < slides.size(); i++)
    {
        SetCar(slides[i], {i+2, 10});
    }

    for (int i = 0; i < slides.size(); i++)
    {
        TUIA::Draw(textImage);
        TUIA::Draw(slides[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}