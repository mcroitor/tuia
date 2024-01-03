#include <fstream>
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
        return lines[point.GetX()][point.GetY()];
    }

    void Image::SetColor(const Point &point, const Color &color)
    {
        lines[point.GetX()][point.GetY()] = color;
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
        // TODO:
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