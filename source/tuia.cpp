#include "tuia.hpp"

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif
#include <iostream>
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
    bool TUIA::_isFrameBuffering = false;
    std::string TUIA::_frameBuffer;

    void TUIA::Write(const std::string& data)
    {
        if (_isFrameBuffering) {
            _frameBuffer += data;
        } else {
            fwrite(data.c_str(), 1, data.size(), stdout);
        }
    }

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
        Write(ColorCode());
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
        Write("\033[?1049h\033[H");
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
        Write(ColorCode());
    }

    void TUIA::SetForegroundColor(const ForegroundColor &foregroundColor)
    {
        _foregroundColor = foregroundColor;
        Write(ColorCode());
    }

    void TUIA::SetBackgroundColor(const BackgroundColor &backgroundColor)
    {
        _backgroundColor = backgroundColor;
        Write(ColorCode());
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
        Write(PointCode(position) + ColorCode() + line);
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
        Write(buffer);
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
        Write(data); // Draw(Point, Image)
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

        Write(data); // Draw(Image)
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
        Write(data);
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
        Write(PointCode(position));
    }

    Point TUIA::GetCursor()
    {
        Point cursor = Point(0, 0);
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO console;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console);
        cursor = Point(console.dwCursorPosition.X, console.dwCursorPosition.Y);
#elif __linux__
        struct termios oldattr, newattr;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        // Request cursor position via ANSI DSR
        write(STDOUT_FILENO, "\033[6n", 4);
        int row = 0, col = 0;
        // Response format: ESC [ row ; col R
        char ch;
        if (read(STDIN_FILENO, &ch, 1) == 1 && ch == '\033' &&
            read(STDIN_FILENO, &ch, 1) == 1 && ch == '[') {
            while (read(STDIN_FILENO, &ch, 1) == 1 && ch != ';') {
                if (ch >= '0' && ch <= '9') row = row * 10 + (ch - '0');
            }
            while (read(STDIN_FILENO, &ch, 1) == 1 && ch != 'R') {
                if (ch >= '0' && ch <= '9') col = col * 10 + (ch - '0');
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        cursor = Point(col - 1, row - 1);
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
        Write(PointCode(position) + ColorCode(_foregroundColor, color) + " " + ColorCode());
    }

    void TUIA::Flush()
    {
        fflush(stdout);
    }

    void TUIA::BeginFrame()
    {
        _isFrameBuffering = true;
        _frameBuffer.clear();
    }

    void TUIA::EndFrame()
    {
        fwrite(_frameBuffer.c_str(), 1, _frameBuffer.size(), stdout);
        fflush(stdout);
        _isFrameBuffering = false;
        _frameBuffer.clear();
    }
}
