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

}