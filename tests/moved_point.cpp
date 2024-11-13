#include "tuia.hpp"

#include <thread>
#include <windows.h>

using usm::graphics::BackgroundColor;
using usm::graphics::ForegroundColor;
using usm::graphics::Image;
using usm::graphics::Point;
using usm::graphics::TUIA;

int Width = 60;
int Height = 23;
int paletteSize = 6;
int knockBack = 0;
Point palette{Width / 2, Height - 1};
Point p{0, 0};

std::mutex mutex;

void quit()
{
    while (true)
    {
        auto qPressed = GetAsyncKeyState('Q');
        if (qPressed)
        {
            TUIA::ResetColors();
            exit(0);
        }
    }
}

void movePalette()
{
    while (true)
    {
        auto leftPressed = GetAsyncKeyState(VK_LEFT);
        auto rightPressed = GetAsyncKeyState(VK_RIGHT);
        mutex.lock();
        if (leftPressed && palette.GetX() > 0)
        {
            palette = {palette.GetX() - 1, palette.GetY()};
        }
        if (rightPressed && palette.GetX() < Width - 1)
        {
            palette = {palette.GetX() + 1, palette.GetY()};
        }
        mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void draw()
{
    BackgroundColor pointColor = BackgroundColor::BrightRed;
    BackgroundColor imageColor = BackgroundColor::BrightBlack;
    BackgroundColor paletteColor = BackgroundColor::BrightGreen;
    auto direction = std::make_pair(1, 1);
    Image image(Width, Height, imageColor);

    while (true)
    {
        mutex.lock();
        TUIA::WriteLine({0, Height + 1}, "Knock back: " + std::to_string(knockBack));
        // put point
        image.SetColor(p, pointColor);
        // put palette
        for (int i = palette.GetX() - paletteSize / 2; i < palette.GetX() + paletteSize / 2; i++)
        {
            image.SetColor({i, Height - 1}, paletteColor);
        }

        // draw image
        TUIA::Draw(image);
        // move point
        image.SetColor(p, imageColor);
        // hide palette
        for (int i = 0; i < Width; i++)
        {
            image.SetColor({i, Height - 1}, imageColor);
        }
        mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        auto px = p.GetX() + direction.first;
        auto py = p.GetY() + direction.second;
        if (px < 0 || px >= Width)
        {
            direction.first = -direction.first;
            px = p.GetX() + direction.first;
        }
        if (py < 0)
        {
            direction.second = -direction.second;
            py = p.GetY() + direction.second;
        }
        // check collision with palette
        if (py == Height - 1)
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (px >= palette.GetX() - paletteSize / 2 && px <= palette.GetX() + paletteSize / 2)
            {
                direction.second = -direction.second;
                py = p.GetY() + direction.second;
                knockBack++;
            }
            else
            {
                TUIA::WriteLine({0, Height + 2}, "Game over!");
                exit(0);
            }
        }
        p = {px, py};
    }
}

int main()
{
    TUIA::Init();
    TUIA::FullScreen();
    TUIA::ClearScreen();
    TUIA::WriteLine({0, Height + 2}, "Press `q` key to exit");

    std::jthread stopThread(quit);
    std::jthread movePaletteThread(movePalette);
    std::jthread drawThread(draw);

    TUIA::ResetColors();
    std::cout << std::endl;
    return 0;
}
