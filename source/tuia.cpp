#include <windows.h>
#include "tuia.hpp"
#include <cstdio>
#include <format>

namespace usm::graphics
{
    using terminal::BackgroundColor;
    using terminal::ForegroundColor;
    using terminal::FromBackgroundColor;
    using terminal::FromForegroundColor;
    using terminal::ToBackgroundColor;
    using terminal::ToForegroundColor;

    BackgroundColor TUIA::_backgroundColor = BackgroundColor::Black;
    ForegroundColor TUIA::_foregroundColor = ForegroundColor::White;

    std::string TUIA::ColorCode()
    {
        return std::format("\033[{};{}m", (int)_foregroundColor, (int)_backgroundColor);
    }

    std::string TUIA::PointCode(const Point &position)
    {
        return std::format("\033[{};{}H", position.GetY(), position.GetX());
    }

    std::string TUIA::ColorCode(ForegroundColor fgColor, BackgroundColor bgColor)
    {
        return std::format("\033[{};{}m", (int)fgColor, (int)bgColor);
    }

    void TUIA::Init()
    {
        std::ios_base::sync_with_stdio(false);
        ResetColors();
        ClearScreen();
    }

    void TUIA::FullScreen()
    {
        HWND console = GetConsoleWindow();
        ShowWindow(console, SW_MAXIMIZE);
    }

    void TUIA::SetWindowSize(uint32_t width, uint32_t height)
    {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, TRUE);
    }

    void TUIA::ResetColors()
    {
        SetForegroundColor(ForegroundColor::White);
        SetBackgroundColor(BackgroundColor::Black);
        PutPoint({0, 0}, BackgroundColor::Black);
    }

    void TUIA::SetForegroundColor(const ForegroundColor &foregroundColor)
    {
        _foregroundColor = foregroundColor;
    }

    void TUIA::SetBackgroundColor(const BackgroundColor &backgroundColor)
    {
        _backgroundColor = backgroundColor;
    }

    void TUIA::SetForegroundColor(const Color &foregroundColor)
    {
        _foregroundColor = ToForegroundColor(foregroundColor);
    }

    void TUIA::SetBackgroundColor(const Color &backgroundColor)
    {
        _backgroundColor = ToBackgroundColor(backgroundColor);
    }

    Color TUIA::GetForegroundColor()
    {
        return FromForegroundColor(_foregroundColor);
    }

    Color TUIA::GetBackgroundColor()
    {
        return FromBackgroundColor(_backgroundColor);
    }

    void TUIA::WriteLine(const Point &position, const std::string &line)
    {
        std::string data = PointCode(position) + ColorCode() + line;
        std::cout << data;
    }

    void TUIA::ClearLine(const Point &position, uint32_t nChars)
    {
        std::string emptyLine(nChars, ' ');
        TUIA::WriteLine(position, emptyLine);
    }

    void TUIA::ClearBlock(const Point &leftTop, const Point &rightBottom)
    {
        size_t nChars = rightBottom.GetX() - leftTop.GetX();
        size_t nLines = rightBottom.GetY() - leftTop.GetY();
        TUIA::ClearBlock(leftTop, nChars, nLines);
    }

    void TUIA::ClearBlock(const Point &position, uint32_t nChars, uint32_t nLines)
    {
        std::string data = "";
        for (uint32_t i = 0; i < nLines; ++i)
        {
            data += PointCode({position.GetX(), position.GetY() + i}) + std::string(nChars, ' ');
        }
        std::cout << data;
    }

    void TUIA::ClearScreen()
    {
        TUIA::ClearBlock(Point(0, 0), TUIA::GetScreenSize());
    }

    void TUIA::Draw(const Point &position, const Image &image)
    {
        std::string data;
        for (uint32_t row = 0; row < image.GetHeight(); ++row)
        {
            data += PointCode({position.GetX(), position.GetY() + row});
            for (uint32_t col = 0; col < image.GetWidth(); ++col)
            {
                auto foreground = _foregroundColor;
                auto background = image.GetColor({col, row});
                data += ColorCode(foreground, background) + image.GetSymbol({col, row});
            }
        }
        puts(data.c_str());
    }

    void TUIA::Draw(const Image &image)
    {
        std::string data = PointCode({0, 0});
        for (uint32_t row = 0; row < image.GetHeight(); ++row)
        {
            for (uint32_t col = 0; col < image.GetWidth(); ++col)
            {
                auto foreground = _foregroundColor;
                auto background = image.GetColor({col, row});
                data += ColorCode(foreground, background) + image.GetSymbol({col, row});
            }
            data += "\n";
        }
        puts(data.c_str());
    }

    void TUIA::Draw(const TextImage &image)
    {
        std::string data = PointCode({0, 0});
        for (uint32_t row = 0; row < image.GetHeight(); ++row)
        {
            for (uint32_t col = 0; col < image.GetWidth(); ++col)
            {
                data += (char)image.GetSymbol({col, row});
            }
            data += "\n";
        }
        puts(data.c_str());
    }

    void TUIA::DrawBlock(const Point &leftTop, uint32_t nChars, uint32_t nLines, const Color &colorBackground)
    {
        Color color = GetBackgroundColor();
        SetBackgroundColor(colorBackground);
        ClearBlock(leftTop, nChars, nLines);
        SetBackgroundColor(color);
    }

    void TUIA::SetCursor(const Point &position)
    {
        std::cout << PointCode(position);
    }

    Point TUIA::GetCursor()
    {
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console);
        return Point(console.dwCursorPosition.X, console.dwCursorPosition.Y);
    }

    Point TUIA::GetScreenSize()
    {
        CONSOLE_SCREEN_BUFFER_INFO console;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console);
        size_t columns = console.srWindow.Right - console.srWindow.Left + 1;
        size_t rows = console.srWindow.Bottom - console.srWindow.Top + 1;

        return Point(columns, rows);
    }

    void TUIA::PutPoint(const Point &position, const Color &color)
    {
        PutPoint(position, ToBackgroundColor(color.ToTerminal()));
    }

    void TUIA::PutPoint(const Point &position, const BackgroundColor &color)
    {
        SetCursor(position);

        std::cout << ColorCode(ForegroundColor::White, color) << " " << ColorCode();
    }
}