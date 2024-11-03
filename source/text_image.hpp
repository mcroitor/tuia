#ifndef _USM_GRAPHICS_TEXT_IMAGE_HPP_
#define _USM_GRAPHICS_TEXT_IMAGE_HPP_

#include "point.hpp"

#include <vector>
#include <string>

namespace usm::graphics::terminal
{
    /**
     * @brief Simple ASCII image representation.
     */
    class TextImage
    {
    public:
        typedef char Symbol;
    private:
        std::vector<std::vector<Symbol>> symbols;

    public:
        TextImage(int width, int height, const Symbol &symbol = ' ');
        TextImage(const TextImage &image);
        int GetWidth() const;
        int GetHeight() const;
        Symbol GetSymbol(const Point &point) const;
        void SetSymbol(const Point &point, const Symbol &symbol);
        void Load(const std::string &filename);
        void Save(const std::string &filename) const;
        TextImage Clone() const;
    };
}
#endif