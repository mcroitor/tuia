#include <windows.h>
#include "tuia.hpp"

namespace usm::graphics
{
    using namespace terminal;

    void TUIA::SetForegroundColor(const ForegroundColor &foregroundColor){
        _foregroundColor = foregroundColor;
    }

    void TUIA::SetBackgroundColor(const BackgroundColor &backgroundColor){
        _backgroundColor = backgroundColor;
    }

    void TUIA::SetForegroundColor(const Color &foregroundColor){
        _foregroundColor = ToForegroundColor(foregroundColor);
    }

    void TUIA::SetBackgroundColor(const Color &backgroundColor){
        _backgroundColor = ToBackgroundColor(backgroundColor);
    }

    Color TUIA::GetForegroundColor() const {
        return FromForegroundColor(_foregroundColor);
    }

    Color TUIA::GetBackgroundColor() const{
        return FromBackgroundColor(_backgroundColor);
    }

    void TUIA::WriteLine(const Point &position, const std::string &line) const{
        TUIA::SetCursor(position);
        // TODO: implement this
    }

    void TUIA::ClearLine(const Point &position, uint32_t nChars) const{
        std::string emptyLine(nChars, ' ');
        TUIA::WriteLine(position, emptyLine);
    }

    void TUIA::ClearBlock(const Point &leftTop, const Point &rightBottom) const{
        size_t nChars = rightBottom.GetX() - leftTop.GetX();
        size_t nLines = rightBottom.GetY() - leftTop.GetY();
        TUIA::ClearBlock(leftTop, nChars, nLines);
    }

    void TUIA::ClearBlock(const Point &position, uint32_t nChars, uint32_t nLines) const{
        for(size_t i = 0; i < nLines; ++i){
            Point pos {position.GetX(), position.GetY() + i};
            TUIA::ClearLine(pos, nChars);
        }
    }

    void TUIA::ClearScreen() const {
        TUIA::ClearBlock(Point(0, 0), TUIA::GetScreenSize());
    }

    void TUIA::Draw(const Point &position, const Image &image) const{
        // TODO: implement this
    }

    void TUIA::SetCursor(const Point & position) const{
        std::cout << "\033[" << position.GetX() << ";" << position.GetY() << "H";
    }

    Point TUIA::GetScreenSize() const {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
  
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return Point(columns, rows);
    }
}