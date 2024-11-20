#include <windows.h>
#include <cstdio>
#include <thread>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include "tuia.hpp"

using namespace usm::graphics;
using namespace usm::graphics::terminal;

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

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
                            image(w - 2, h - 2),
                            buffer(w, h),
                            cursor({1, 1})
    {
        SetBuffer();
    }

    void SetBuffer()
    {
        // draw border of screen buffer
        buffer.SetPart({0, 0}, TextImage(width, 1, '#'));
        buffer.SetPart({0, height - 1}, TextImage(width, 1, '#'));
        buffer.SetPart({0, 0}, TextImage(1, height, '#'));
        buffer.SetPart({width - 1, 0}, TextImage(1, height, '#'));
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
        int key = getch();
        int x, y;
        switch (key)
        {
            // move cursor
        case '\033':
            getch();
            switch (getch())
            {
            case 'A':
                y = cursor.GetY() == 1 ? cursor.GetY() : cursor.GetY() - 1;
                cursor = {cursor.GetX(), y};
                break;
            case 'B':
                y = cursor.GetY() == height - 2 ? cursor.GetY() : cursor.GetY() + 1;
                cursor = {cursor.GetX(), y};
                break;
            case 'C':
                x = cursor.GetX() == width - 2 ? cursor.GetX() : cursor.GetX() + 1;
                cursor = {x, cursor.GetY()};
                break;
            case 'D':
                x = cursor.GetX() == 1 ? cursor.GetX() : cursor.GetX() - 1;
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
        TUIA::WriteLine({1, height + 2}, "Image name:");
        std::string filename;
        std::cin >> filename;
        image.Save(filename + ".txt");
        TUIA::WriteLine({1, width + 2}, "Image saved to " + filename);
        TUIA::Flush();
    }

    void SaveAll()
    {
        std::string filename = "image_" + std::to_string(std::time(0)) + ".txt";
        image.Save(filename);
        TUIA::WriteLine({1, height + 2}, "Image saved to " + filename);
        TUIA::Flush();
    }

    void Load()
    {
        TUIA::WriteLine({1, height + 2}, "Image name:");
        std::string filename;
        std::cin >> filename;
        image.Load(filename + ".txt");
        TUIA::WriteLine({1, height + 2}, "Image loaded from " + filename);
        TUIA::Flush();
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
        painter.SetBuffer();
        painter.Draw();
        painter.DoAction();
    }
    return 0;
}