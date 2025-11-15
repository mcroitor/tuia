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

    void TUIA::SetColors(const ForegroundColor &foregroundColor, const BackgroundColor &backgroundColor)
    {
        _foregroundColor = foregroundColor;
        _backgroundColor = backgroundColor;
        std::cout << ColorCode();
    }

    void TUIA::Init()
    {
        std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
        auto stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode(stdoutHandle, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
        SetConsoleMode(stdoutHandle, consoleMode);
#elif __linux__
        // accelerate output
#endif

        ResetColors();
        ClearScreen();
    }

    void TUIA::FullScreen()
    {
#ifdef _WIN32
        HWND console = GetConsoleWindow();
        ShowWindow(console, SW_MAXIMIZE);
#elif __linux__
        std::cout << "\033[?1049h\033[H";
#endif
    }

    void TUIA::SetWindowSize(int width, int height)
    {
#ifdef _WIN32
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, TRUE);
#elif __linux__
        // resize terminal window
#endif
    }

    void TUIA::ResetColors()
    {
        SetForegroundColor(ForegroundColor::White);
        SetBackgroundColor(BackgroundColor::Black);
        std::cout << ColorCode();
    }

    void TUIA::SetForegroundColor(const ForegroundColor &foregroundColor)
    {
        _foregroundColor = foregroundColor;
        std::cout << ColorCode();
    }

    void TUIA::SetBackgroundColor(const BackgroundColor &backgroundColor)
    {
        _backgroundColor = backgroundColor;
        std::cout << ColorCode();
    }

    void TUIA::SetForegroundColor(const Color &foregroundColor)
    {
        SetForegroundColor(ToForegroundColor(foregroundColor));
    }

    void TUIA::SetBackgroundColor(const Color &backgroundColor)
    {
        SetBackgroundColor(ToBackgroundColor(backgroundColor));
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
        std::string buffer = ColorCode();
        buffer.reserve(nLines * (nChars + 10));
        for (int i = 0; i < nLines; ++i)
        {
            buffer += PointCode({position.GetX(), position.GetY() + i})
                + std::string(nChars, ' ');
        }
        fwrite(buffer.c_str(), 1, buffer.size(), stdout);
    }

    void TUIA::ClearScreen()
    {
        TUIA::ClearBlock(Point(0, 0), TUIA::GetScreenSize());
    }

    void TUIA::Draw(const Point &position, const Image &image)
    {
        auto foreground = _foregroundColor;
        auto background = image.GetColor({0, 0});

        std::string data;
        data.reserve(image.GetHeight() * image.GetWidth() * 8); // Estimate size
        for (int row = 0; row < image.GetHeight(); ++row)
        {
            data += PointCode({position.GetX(), position.GetY() + row});
            for (int col = 0; col < image.GetWidth(); ++col)
            {
                if(background != image.GetColor({col, row})) {
                    background = image.GetColor({col, row});
                    data += ColorCode(foreground, background);
                }
                data += image.GetSymbol({col, row});
            }
        }
        fwrite(data.c_str(), 1, data.size(), stdout);
    }

    void TUIA::Draw(const Image &image)
    {
        auto foreground = _foregroundColor;
        auto background = image.GetColor({0, 0});
        std::string data = PointCode({0, 0}) + ColorCode(_foregroundColor, background);
        data.reserve(image.GetHeight() * image.GetWidth() * 8); // Estimate size

        for (int row = 0; row < image.GetHeight(); ++row)
        {
            for (int col = 0; col < image.GetWidth(); ++col)
            {
                if(background != image.GetColor({col, row})) {
                    background = image.GetColor({col, row});
                    data += ColorCode(foreground, background);
                }
                data += image.GetSymbol({col, row});
            }
            data += '\n';
        }

        fwrite(data.c_str(), 1, data.size(), stdout);
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
            data += '\n';
        }
        fwrite(data.c_str(), 1, data.size(), stdout);
    }

    void TUIA::DrawBlock(const Point &leftTop, int nChars, int nLines, const BackgroundColor &colorBackground)
    {
        Color color = GetBackgroundColor();
        SetBackgroundColor(colorBackground);
        ClearBlock(leftTop, nChars, nLines);
        SetBackgroundColor(color);
    }

    void TUIA::DrawBlock(const Point &leftTop, int nChars, int nLines, const Color &colorBackground)
    {
        DrawBlock(leftTop, nChars, nLines, ToBackgroundColor(colorBackground));
    }

    void TUIA::SetCursor(const Point &position)
    {
        std::cout << PointCode(position);
    }

    Point TUIA::GetCursor()
    {
        Point cursor = Point(0, 0);
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console);
        cursor = Point(console.dwCursorPosition.X, console.dwCursorPosition.Y);
#elif __linux__
        // get cursor position
        // TODO: implement
#endif
        return cursor;
    }

    Point TUIA::GetScreenSize()
    {
        Point screenSize = Point(0, 0);
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console);
        int columns = console.srWindow.Right - console.srWindow.Left + 1;
        int rows = console.srWindow.Bottom - console.srWindow.Top + 1;
        screenSize = Point(columns, rows);
#elif __linux__
        // get screen size
        #include <sys/ioctl.h>
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        screenSize = Point(w.ws_col, w.ws_row);
#else
        screenSize = Point(120, 32);
#endif
        return screenSize;
    }

    void TUIA::PutPoint(const Point &position, const Color &color)
    {
        PutPoint(position, ToBackgroundColor(color.ToTerminal()));
    }

    void TUIA::PutPoint(const Point &position, const BackgroundColor &color)
    {
        std::string buffer = PointCode(position)
            + ColorCode(_foregroundColor, color)
            + " " + ColorCode();
        fwrite(buffer.c_str(), 1, buffer.size(), stdout);
    }

    void TUIA::Flush()
    {
        fflush(stdout);
    }
}
