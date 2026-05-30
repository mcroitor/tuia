#include "tuia.hpp"

#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <thread>

using usm::graphics::BackgroundColor;
using usm::graphics::Color;
using usm::graphics::Image;
using usm::graphics::Point;
using usm::graphics::TUIA;
using usm::graphics::terminal::FromBackgroundColor;

// Clock image dimensions
static const int IMG_W  = 80;
static const int IMG_H  = 40;
static const int CX     = IMG_W / 2;   // center x
static const int CY     = IMG_H / 2;   // center y
static const int RADIUS = 17;

// Terminal cells are roughly twice as tall as wide.
// Scaling x by ASPECT makes lines/circles look correct on screen.
static const double ASPECT = 2.0;
static const double PI     = std::acos(-1.0);

static Color ToC(BackgroundColor bc) { return FromBackgroundColor(bc); }

// Draw the clock outline as an aspect-ratio-corrected ellipse.
static void DrawFace(Image& img)
{
    for (int step = 0; step < 720; ++step) {
        double rad = step * PI / 360.0;
        int x = CX + (int)std::round(RADIUS * ASPECT * std::cos(rad));
        int y = CY + (int)std::round(RADIUS        * std::sin(rad));
        img.SetColor({x, y}, BackgroundColor::BrightWhite);
    }
}

// Draw hour (depth 2) and minute (depth 1) tick marks.
static void DrawTicks(Image& img)
{
    for (int tick = 0; tick < 60; ++tick) {
        double angle = tick * 2.0 * PI / 60.0;
        bool isHour  = (tick % 5 == 0);
        int  innerR  = RADIUS - (isHour ? 2 : 1);
        BackgroundColor color = isHour ? BackgroundColor::BrightCyan
                                       : BackgroundColor::Cyan;
        for (int r = innerR; r < RADIUS; ++r) {
            int x = CX + (int)std::round(r * ASPECT * std::sin(angle));
            int y = CY - (int)std::round(r           * std::cos(angle));
            img.SetColor({x, y}, color);
        }
    }
}

// Draw a single clock hand from center toward angle_rad with given length.
static void DrawHand(Image& img, double angle_rad, int length, BackgroundColor color)
{
    Point end{
        CX + (int)std::round(length * ASPECT * std::sin(angle_rad)),
        CY - (int)std::round(length           * std::cos(angle_rad))
    };
    img.DrawLine({CX, CY}, end, ToC(color));
}

int main()
{
    TUIA::Init();
    TUIA::ClearScreen();
    TUIA::FullScreen();

    // Position clock in the center of the terminal.
    Point screen = TUIA::GetScreenSize();
    int ox = std::max(0, (screen.GetX() - IMG_W) / 2);
    int oy = std::max(0, (screen.GetY() - IMG_H) / 2);

    while (true) {
        // Current local time
        std::time_t now = std::time(nullptr);
        std::tm*    t   = std::localtime(&now);
        int hours   = t->tm_hour % 12;
        int minutes = t->tm_min;
        int seconds = t->tm_sec;

        // Smooth continuous hand angles (clockwise from 12)
        double secAngle = seconds               * 2.0 * PI / 60.0;
        double minAngle = (minutes + seconds / 60.0)  * 2.0 * PI / 60.0;
        double hrAngle  = (hours   + minutes / 60.0)  * 2.0 * PI / 12.0;

        // Build clock image
        Image img(IMG_W, IMG_H, BackgroundColor::Black);
        DrawFace(img);
        DrawTicks(img);
        DrawHand(img, hrAngle,   9, BackgroundColor::BrightYellow);  // hour
        DrawHand(img, minAngle, 13, BackgroundColor::BrightGreen);   // minute
        DrawHand(img, secAngle, 15, BackgroundColor::BrightRed);     // second
        img.SetColor({CX, CY},      BackgroundColor::BrightWhite);  // center dot

        // Digital readout below the face
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(2) << t->tm_hour << ':'
            << std::setw(2) << minutes    << ':'
            << std::setw(2) << seconds;

        // Atomic frame render
        TUIA::BeginFrame();
        TUIA::Draw({ox, oy}, img);
        TUIA::SetForegroundColor(Color(255, 255, 255));
        TUIA::SetBackgroundColor(BackgroundColor::Black);
        TUIA::WriteLine({ox + CX - 4, oy + IMG_H + 1}, oss.str());
        TUIA::EndFrame();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
