#include "tuia.hpp"

#include <windows.h>
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

    void TUIA::SetWindowSize(int width, int height)
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

    void TUIA::ClearLine(const Point &position, int nChars)
    {
        std::string emptyLine(nChars, ' ');
        TUIA::WriteLine(position, emptyLine);
    }

    void TUIA::ClearBlock(const Point &leftTop, const Point &rightBottom)
    {
        int nChars = rightBottom.GetX() - leftTop.GetX();
        int nLines = rightBottom.GetY() - leftTop.GetY();
        TUIA::ClearBlock(leftTop, nChars, nLines);
    }

    void TUIA::ClearBlock(const Point &position, int nChars, int nLines)
    {
        std::string data = "";
        for (int i = 0; i < nLines; ++i)
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
        for (int row = 0; row < image.GetHeight(); ++row)
        {
            data += PointCode({position.GetX(), position.GetY() + row});
            for (int col = 0; col < image.GetWidth(); ++col)
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
        for (int row = 0; row < image.GetHeight(); ++row)
        {
            for (int col = 0; col < image.GetWidth(); ++col)
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
        for (int row = 0; row < image.GetHeight(); ++row)
        {
            for (int col = 0; col < image.GetWidth(); ++col)
            {
                data += (char)image.GetSymbol({col, row});
            }
            data += "\n";
        }
        puts(data.c_str());
    }

    void TUIA::DrawBlock(const Point &leftTop, int nChars, int nLines, const Color &colorBackground)
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
        int columns = console.srWindow.Right - console.srWindow.Left + 1;
        int rows = console.srWindow.Bottom - console.srWindow.Top + 1;
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