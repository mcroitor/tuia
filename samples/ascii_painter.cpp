#include <cstdio>
#include <thread>
#include <ctime>
#include "tuia.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__)
#include <windows.h>
static int read_char()
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode = 0;
    // SetConsoleMode only has effect when hIn is a real console (not a pipe/PTY).
    // GetConsoleMode fails gracefully on PTYs (e.g. mintty), so we check first.
    BOOL isConsole = GetConsoleMode(hIn, &prevMode);
    if (isConsole) {
        SetConsoleMode(hIn, prevMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
    }
    char c = '\0';
    DWORD nRead = 0;
    ReadFile(hIn, &c, 1, &nRead, nullptr);
    if (isConsole) {
        SetConsoleMode(hIn, prevMode);
    }
    return (unsigned char)c;
}
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <termios.h>
#include <unistd.h>
static int read_char()
{
    struct termios oldattr, newattr;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#else
static int read_char() { return getchar(); }
#endif

using namespace usm::graphics;
using namespace usm::graphics::terminal;


/*********************************************************
 * |                        80                         |
 * |             60                          | 20      |
 * +-----------------------------------------+---------+ --
 * |                                         |         |
 * |  +-----------------------------------+  |         |
 * |  |                                   |  |         |
 * |  |                                   |  |         |
 * |  |                                   |  |         |
 * |  |                                   |  |         | 32
 * |  |                                   |  |         |
 * |  |                                   |  |         |
 * |  |                                   |  |         |
 * |  +-----------------------------------+  |         |
 * |                                         |         |
 * +---------------------------------------------------+ --
 *********************************************************/

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 32;

const char CURSOR = 'X';

class Painter
{
private:
    int width;
    int height;
    TextImage image;
    TextImage buffer;
    Point cursor;

public:
    Painter(int w, int h) : width(w),
                            height(h),
                            image(w, h),
                            buffer(w + 2, h + 2),
                            cursor({1, 1})
    {
        SetBuffer();
    }

    void SetBuffer()
    {
        // draw border of screen buffer
        buffer.SetPart({0, 0}, TextImage(width + 2, 1, '#'));
        buffer.SetPart({0, height + 1}, TextImage(width + 2, 1, '#'));
        buffer.SetPart({0, 0}, TextImage(1, height + 1, '#'));
        buffer.SetPart({width + 1, 0}, TextImage(1, height + 1, '#'));
        // draw image
        buffer.SetPart({1, 1}, image);
        // draw cursor
        buffer.SetSymbol(cursor, CURSOR);
    }

    void Draw()
    {
        TUIA::Draw(buffer);
    }
    void DoAction()
    {
        int key = read_char();
        int x, y;
        switch (key)
        {
            // move cursor
        case '\033':
            read_char();
            switch (read_char())
            {
            case 'A':
                y = cursor.GetY() == 1 ? 1 : cursor.GetY() - 1;
                cursor = {cursor.GetX(), y};
                break;
            case 'B':
                y = cursor.GetY() == height ? height : cursor.GetY() + 1;
                cursor = {cursor.GetX(), y};
                break;
            case 'C':
                x = cursor.GetX() == width ? width : cursor.GetX() + 1;
                cursor = {x, cursor.GetY()};
                break;
            case 'D':
                x = cursor.GetX() == 1 ? 1 : cursor.GetX() - 1;
                cursor = {x, cursor.GetY()};
                break;
            // escape pressed
            case 27:
                exit(0);
                break;
            }
            break;
        case '0':
            image.Clear();
            break;
        case '1':
            Save();
            break;
        case '2':
            SaveAll();
            break;
        // system keys
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            Load();
            break;
        default:
            // put symbol
            PutSymbol(key);
        }
    }

    void PutSymbol(int key)
    {
        image.SetSymbol({cursor.GetX() - 1, cursor.GetY() - 1}, key);
    }

    void Save()
    {
        TUIA::WriteLine({1, height + 3}, "Image name:");
        std::string filename;
        std::cin >> filename;
        try
        {
            image.Save(filename + ".txt");
            TUIA::WriteLine({1, width + 3}, "Image saved to " + filename);
        }
        catch (const std::exception &e)
        {
            TUIA::WriteLine({1, width + 3}, e.what());
        }
        TUIA::Flush();
    }

    void SaveAll()
    {
        std::string filename = "image_" + std::to_string(std::time(0)) + ".txt";
        try
        {
            image.Save(filename + ".txt");
            TUIA::WriteLine({1, width + 3}, "Image saved to " + filename);
        }
        catch (const std::exception &e)
        {
            TUIA::WriteLine({1, width + 3}, e.what());
        }
        TUIA::Flush();
    }

    void Load()
    {
        TUIA::WriteLine({1, height + 3}, "Image name:");
        std::string filename;
        std::cin >> filename;
        image.Load(filename + ".txt");
        width = image.GetWidth();
        height = image.GetHeight();
        // resize buffer
        buffer = TextImage(width + 2, height + 2);
        TUIA::ClearScreen();
        SetBuffer();
        //write status
        TUIA::WriteLine({1, height + 3}, "Image loaded from " + filename);
        TUIA::Flush();
    }

    void Info()
    {
        // Info panel: 4 symbols left from right bottom corner
        // 1. Cursor position
        TUIA::WriteLine({width + 4, 2}, "Cursor: " + std::to_string(cursor.GetX()) + ", " + std::to_string(cursor.GetY()));
        // 2. Image size
        TUIA::WriteLine({width + 4, 3}, "Size: " + std::to_string(image.GetWidth()) + "x" + std::to_string(image.GetHeight()));
        // 3. How to quit
        TUIA::WriteLine({width + 4, 4}, "3 x ESC - quit");
        // 4. How to save
        TUIA::WriteLine({width + 4, 5}, "1 \t- save");
        TUIA::WriteLine({width + 4, 6}, "2 \t- save auto");
        // 5. How to load
        TUIA::WriteLine({width + 4, 7}, "3 \t- load");
        // 6. How to clear
        TUIA::WriteLine({width + 4, 8}, "0 \t- clear");
    }
};

int main(int argc, char **argv)
{
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    if (argc == 3)
    {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    TUIA::Init();
    TUIA::ClearScreen();
    Painter painter(width, height);
    while (true)
    {
        painter.Info();
        TUIA::Flush();
        painter.SetBuffer();
        painter.Draw();
        painter.DoAction();
    }
    return 0;
}