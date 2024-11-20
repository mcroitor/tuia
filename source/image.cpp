#include <fstream>
#include <sstream>
#include "image.hpp"

namespace usm::graphics
{
    Image::Image(int width, int height, const BackgroundColor &color) :
        lines(height, std::vector<BackgroundColor>(width, color)),
        symbols(height, std::vector<char>(width, ' '))
    {
    }

    BackgroundColor Image::GetColor(const Point &point) const
    {
        return lines[point.GetY()][point.GetX()];
    }

    void Image::SetColor(const Point &point, const Color &color)
    {
        SetColor(point, ToBackgroundColor(color));
    }

    void Image::SetColor(const Point &point, const BackgroundColor &color)
    {
        lines[point.GetY()][point.GetX()] = color;
    }

    void Image::SetPixel(const Point &point, const Color &color)
    {
        SetColor(point, color);
    }

    void Image::SetPixel(const Point &point, const BackgroundColor &color)
    {
        SetColor(point, color);
    }
    
    int Image::GetWidth() const
    {
        return lines[0].size();
    }

    int Image::GetHeight() const
    {
        return lines.size();
    }

    char Image::GetSymbol(const Point &point) const
    {
        return symbols[point.GetY()][point.GetX()];
    }

    void Image::SetSymbol(const Point &point, const char &symbol)
    {
        symbols[point.GetY()][point.GetX()] = symbol;
    }

    void Image::Load(const std::string& filename){
        std::ifstream fin(filename.c_str());
        std::string line;
        int width, height;
        fin >> width >> height;
        lines.resize(width, std::vector<BackgroundColor>(height, BackgroundColor::Black));
        symbols.resize(width, std::vector<char>(height, ' '));
        for(int row = 0; row < GetHeight(); ++row) {
            for(int col = 0; col < GetWidth(); ++col) {
                Color color;
                fin >> color;
                lines[row][col] = ToBackgroundColor(color);
                fin >> symbols[row][col];
            }
        }
    }
    
    void Image::Save(const std::string& filename) const{
        std::ofstream fout(filename.c_str());
        fout << GetWidth() << " " << GetHeight() << std::endl;
        for(int row = 0; row  < GetHeight(); ++row) {
            for(int col = 0; col < GetWidth(); ++col) {
                fout << FromBackgroundColor(lines[row][col]) << " ";
                fout << symbols[row][col] << " ";
            }
            fout << std::endl;
        }
    }

    Image Image::Clone() const{
        Image img(GetWidth(), GetHeight());
        img.lines = lines;
        img.symbols = symbols;
        return img;
    }

}