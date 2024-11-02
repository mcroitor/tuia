#ifndef _USM_GRAPHICS_IMAGE_HPP_
#define _USM_GRAPHICS_IMAGE_HPP_

#include <cstdint>
#include <vector>
#include "color.hpp"
#include "terminal_color.hpp"
#include "point.hpp"

using namespace usm::graphics::terminal;

namespace usm::graphics
{
    /**
     * @brief Simple image representation. Image is a vector of lines.
     * Line is a vector of colors.
     */
    class Image
    {
        std::vector<std::vector<BackgroundColor>> lines;
        std::vector<std::vector<char>> symbols;

    public:
        /**
         * @brief Create a Image object with width x height dimensions.
         */
        Image(uint32_t width, uint32_t height, const BackgroundColor &color = BackgroundColor::Black);
        /**
         * @brief Return color of specified pixel.
         * @param Point point coordinate of pixel
         * @return BackgroundColor
         */
        BackgroundColor GetColor(const Point &point) const;
        /**
         * @brief Set a pixel color.
         * @param Point point coordinate of pixel
         * @param BackgroundColor color
         */
        void SetColor(const Point &point, const BackgroundColor &color);
        /**
         * @brief Set a pixel color.
         * @param Point point coordinate of pixel
         * @param Color color
         */
        void SetColor(const Point &point, const Color &color);
        /**
         * @brief Return width of image
         * @return uint32_t
         */
        uint32_t GetWidth() const;
        /**
         * @brief Return height of image
         * @return uint32_t
         */
        uint32_t GetHeight() const;
        /**
         * @brief Return symbol of specified pixel.
         * @param Point point coordinate of pixel
         * @return char
         */
        char GetSymbol(const Point &point) const;
        /**
         * @brief Set a pixel symbol.
         * @param Point point coordinate of pixel
         * @param char symbol
         */
        void SetSymbol(const Point &point, const char &symbol);
        /**
         * @brief Load image from file
         * @return std::string filename
         */
        void Load(const std::string &filename);
        /**
         * @brief Save image to file
         */
        void Save(const std::string &filename) const;
        /**
         * @brief Clone image
         * @return Image
         */
        Image Clone() const;
    };
}
#endif