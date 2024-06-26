#include <fstream>
#include <sstream>
#include "image.hpp"

namespace usm::graphics
{
    Image::Image(uint32_t width, uint32_t height)
    {
        lines.resize(width);
        for(auto& points: lines){
            points.resize(height, Color());
        }
    }

    Color Image::GetColor(const Point &point) const
    {
        return lines[point.X()][point.Y()];
    }

    void Image::SetColor(const Point &point, const Color &color)
    {
        lines[point.X()][point.Y()] = color;
    }

    void Image::DrawLine(const Point &start, const Point &end, const Color &color)
    {
        int dx = end.X() - start.X();
        int dy = end.Y() - start.Y();
        int steps = std::max(std::abs(dx), std::abs(dy));
        float xInc = dx / (float)steps;
        float yInc = dy / (float)steps;
        float x = start.X();
        float y = start.Y();
        for(int i = 0; i < steps; ++i){
            SetColor({(uint32_t)x, (uint32_t)y}, color);
            x += xInc;
            y += yInc;
        }
    }
    
    uint32_t Image::GetWidth() const
    {
        return lines.size();
    }

    uint32_t Image::GetHeight() const
    {
        return lines[0].size();
    }

    void Image::Load(const std::string& filename){
        std::ifstream fin(filename.c_str());
        std::string line;
        uint32_t row = 0;
        while(std::getline(fin, line)){
            std::istringstream iss(line);
            uint32_t col = 0;
            Color color;
            while(iss >> color){
                SetColor({col, row}, color);
                ++col;
            }
            ++row;
        }
    }
    
    void Image::Save(const std::string& filename) const{
        std::ofstream fout(filename.c_str());
        for(uint32_t row = 0; row  < GetWidth(); ++row) {
            for(uint32_t col = 0; col < GetHeight(); ++col) {
                fout << lines[row][col] << " ";
            }
            fout << std::endl;
        }
    }
}