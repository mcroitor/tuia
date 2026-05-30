#include <algorithm>
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
        if (!In(point)) {
            return BackgroundColor::Black;
        }
        return lines[point.GetY()][point.GetX()];
    }

    void Image::SetColor(const Point &point, const Color &color)
    {
        SetColor(point, ToBackgroundColor(color));
    }

    void Image::SetColor(const Point &point, const BackgroundColor &color)
    {
        if (!In(point)) {
            return;
        }
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
        if (lines.empty()) return 0;
        return lines[0].size();
    }

    int Image::GetHeight() const
    {
        return lines.size();
    }

    char Image::GetSymbol(const Point &point) const
    {
        if (!In(point)) {
            return ' ';
        }
        return symbols[point.GetY()][point.GetX()];
    }

    void Image::SetSymbol(const Point &point, const char &symbol)
    {
        if (!In(point)) {
            return;
        }
        symbols[point.GetY()][point.GetX()] = symbol;
    }

    void Image::Load(const std::string& filename){
        std::ifstream fin(filename.c_str());
        if (!fin.is_open()) {
            return;
        }
        int width, height;
        // Detect versioned format ("TUIA_IMG <version>") vs legacy ("<width> <height>")
        std::string firstToken;
        if (!(fin >> firstToken)) return;
        if (firstToken == "TUIA_IMG") {
            int version;
            if (!(fin >> version)) return; // consume version number
            if (!(fin >> width >> height) || width <= 0 || height <= 0) return;
        } else {
            // Legacy format: firstToken is the width
            try { width = std::stoi(firstToken); } catch (...) { return; }
            if (!(fin >> height) || width <= 0 || height <= 0) return;
        }
        lines.assign(height, std::vector<BackgroundColor>(width, BackgroundColor::Black));
        symbols.assign(height, std::vector<char>(width, ' '));
        for(int row = 0; row < height; ++row) {
            for(int col = 0; col < width; ++col) {
                Color color;
                fin >> color;
                lines[row][col] = ToBackgroundColor(color);
                fin >> symbols[row][col];
            }
        }
    }
    
    void Image::Save(const std::string& filename) const{
        std::ofstream fout(filename.c_str());
        fout << "TUIA_IMG 1\n";
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

    bool Image::In(const Point& point) const
    {
        return point.GetY() >= 0 && point.GetY() < GetHeight() &&
               point.GetX() >= 0 && point.GetX() < GetWidth();
    }

    void Image::DrawLine(const Point& start, const Point& end, const Color& color)
    {
        int x0 = start.GetX(), y0 = start.GetY();
        int x1 = end.GetX(),   y1 = end.GetY();
        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;
        while (true) {
            SetColor(Point(x0, y0), color);
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 <  dx) { err += dx; y0 += sy; }
        }
    }

    void Image::DrawRect(const Point& topLeft, int width, int height, const BackgroundColor& color, bool filled)
    {
        if (filled) {
            for (int row = 0; row < height; ++row) {
                for (int col = 0; col < width; ++col) {
                    SetColor(Point(topLeft.GetX() + col, topLeft.GetY() + row), color);
                }
            }
        } else {
            for (int col = 0; col < width; ++col) {
                SetColor(Point(topLeft.GetX() + col, topLeft.GetY()), color);
                SetColor(Point(topLeft.GetX() + col, topLeft.GetY() + height - 1), color);
            }
            for (int row = 1; row < height - 1; ++row) {
                SetColor(Point(topLeft.GetX(), topLeft.GetY() + row), color);
                SetColor(Point(topLeft.GetX() + width - 1, topLeft.GetY() + row), color);
            }
        }
    }

    void Image::DrawCircle(const Point& center, int radius, const BackgroundColor& color)
    {
        // Midpoint circle algorithm
        auto plot8 = [&](int cx, int cy) {
            SetColor(Point(center.GetX() + cx, center.GetY() + cy), color);
            SetColor(Point(center.GetX() - cx, center.GetY() + cy), color);
            SetColor(Point(center.GetX() + cx, center.GetY() - cy), color);
            SetColor(Point(center.GetX() - cx, center.GetY() - cy), color);
            SetColor(Point(center.GetX() + cy, center.GetY() + cx), color);
            SetColor(Point(center.GetX() - cy, center.GetY() + cx), color);
            SetColor(Point(center.GetX() + cy, center.GetY() - cx), color);
            SetColor(Point(center.GetX() - cy, center.GetY() - cx), color);
        };
        int x = 0, y = radius;
        int d = 1 - radius;
        while (x <= y) {
            plot8(x, y);
            if (d < 0) {
                d += 2 * x + 3;
            } else {
                d += 2 * (x - y) + 5;
                --y;
            }
            ++x;
        }
    }

    void Image::Fill(const BackgroundColor& color)
    {
        for (auto& row : lines) {
            std::fill(row.begin(), row.end(), color);
        }
    }

}