#ifndef _USM_GRAPHICS_IMAGE_HPP_
#define _USM_GRAPHICS_IMAGE_HPP_

#include <cstdint>
#include <vector>
#include "color.hpp"
#include "point.hpp"

namespace usm::graphics
{
    /**
     * @brief Simple image representation. Image is a vector of lines.
     * Line is a vector of colors.
     */
    class Image
    {
        std::vector<std::vector<Color> > lines;
    public:
        /**
         * @brief Create a Image object with width x height dimensions.
         */
        Image(uint32_t width, uint32_t height);
        /**
         * @brief Return color of specified pixel.
         * @param Point point coordinate of pixel
         * @return Color
         */
        Color GetColor(const Point& point) const;
        /**
         * @brief Set a pixel color.
         * @param Point point coordinate of pixel
         * @param Color color
         */
        void SetColor(const Point& point, const Color& color);
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
         * @brief Load image from file
         * @return std::string filename
         */
        void Load(const std::string& filename);
        /**
         * @brief Save image to file
         */
        void Save(const std::string& filename) const;
    };
}
#endif