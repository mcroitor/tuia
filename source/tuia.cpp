#include <windows.h>
#include "tuia.hpp"

namespace usm::graphics
{
    using terminal::BackgroundColor;
    using terminal::ForegroundColor;
    using terminal::ToBackgroundColor;
    using terminal::ToForegroundColor;
    using terminal::FromBackgroundColor;
    using terminal::FromForegroundColor;

    BackgroundColor TUIA::_backgroundColor = BackgroundColor::Black;
    ForegroundColor TUIA::_foregroundColor = ForegroundColor::White;

    std::string TUIA::ColorCode() {
        return std::string("\033[") 
            + std::to_string((int)_foregroundColor) 
            + std::string(";") 
            + std::to_string((int)_backgroundColor)
            + std::string("m");
    }

    std::string TUIA::ColorCode(ForegroundColor fgColor, BackgroundColor bgColor) {
        return std::string("\033[") 
            + std::to_string((int)fgColor) 
            + std::string(";") 
            + std::to_string((int)bgColor)
            + std::string("m");
    }

    void TUIA::Init() {
        ResetColors();
        ClearScreen();
    }

    void TUIA::ResetColors(){
        SetForegroundColor(ForegroundColor::White);
        SetBackgroundColor(BackgroundColor::Black);
    }

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

    Color TUIA::GetForegroundColor() {
        return FromForegroundColor(_foregroundColor);
    }

    Color TUIA::GetBackgroundColor() {
        return FromBackgroundColor(_backgroundColor);
    }

    void TUIA::WriteLine(const Point &position, const std::string &line) {
        TUIA::SetCursor(position);
        std::cout << ColorCode() << line;
    }

    void TUIA::ClearLine(const Point &position, uint32_t nChars) {
        std::string emptyLine(nChars, ' ');
        TUIA::WriteLine(position, emptyLine);
    }

    void TUIA::ClearBlock(const Point &leftTop, const Point &rightBottom) {
        size_t nChars = rightBottom.GetX() - leftTop.GetX();
        size_t nLines = rightBottom.GetY() - leftTop.GetY();
        TUIA::ClearBlock(leftTop, nChars, nLines);
    }

    void TUIA::ClearBlock(const Point &position, uint32_t nChars, uint32_t nLines) {
        for(uint32_t i = 0; i < nLines; ++i){
            Point pos {position.GetX(), position.GetY() + i};
            TUIA::ClearLine(pos, nChars);
        }
    }

    void TUIA::ClearScreen() {
        TUIA::ClearBlock(Point(0, 0), TUIA::GetScreenSize());
    }

    void TUIA::Draw(const Point &position, const Image &image) {
        for(uint32_t col = 0; col < image.GetWidth(); ++col) {
            for(uint32_t row = 0; row < image.GetHeight(); ++row) {
                PutPoint({position.GetX() + col, position.GetY() + row}, image.GetColor({col, row}));
            }
        }
    }

    void TUIA::DrawBlock(const Point &leftTop, uint32_t nChars, uint32_t nLines, const Color &colorBackground) {
        Color color = GetBackgroundColor();
        SetBackgroundColor(colorBackground);
        ClearBlock(leftTop, nChars, nLines);
        SetBackgroundColor(color);
    }

    void TUIA::SetCursor(const Point & position) {
        std::cout << "\033[" << position.GetY() << ";" << position.GetX() << "H";
    }

    Point TUIA::GetScreenSize() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
  
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        size_t columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size_t rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return Point(columns, rows);
    }

    void TUIA::PutPoint(const Point& position, const Color& color) {
        PutPoint(position, ToBackgroundColor(color.ToTerminal()));
    }

    void TUIA::PutPoint(const Point& position, const BackgroundColor& color) {
        SetCursor(position);

        std::cout << ColorCode(ForegroundColor::White, color) << " " << ColorCode();
    }
}