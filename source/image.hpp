#ifndef _USM_GRAPHICS_IMAGE_HPP_
#define _USM_GRAPHICS_IMAGE_HPP_

#include <cstdint>
#include <vector>
#include "color.hpp"
#include "background_color.hpp"
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
        Image(int width, int height, const BackgroundColor &color = BackgroundColor::Black);
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
         * @param BackgroundColor color
         */
        void SetPixel(const Point &point, const BackgroundColor &color);
        /**
         * @brief Set a pixel color.
         * @param Point point coordinate of pixel
         * @param Color color
         */
        void SetColor(const Point &point, const Color &color);
        /**
         * @brief Set a pixel color.
         * @param Point point coordinate of pixel
         * @param Color color
         */
        void SetPixel(const Point &point, const Color &color);
        /**
         * @brief Draw a line between two points.
         * @param Point start
         * @param Point end
         * @param Color color
         */
        void DrawLine(const Point& start, const Point& end, const Color& color);
        /**
         * @brief Draw a rectangle.
         * @param topLeft top-left corner of the rectangle
         * @param width rectangle width in pixels
         * @param height rectangle height in pixels
         * @param color pixel color
         * @param filled if true, draws a filled rectangle; otherwise draws outline only
         */
        void DrawRect(const Point& topLeft, int width, int height, const BackgroundColor& color, bool filled = true);
        /**
         * @brief Draw a circle outline using the midpoint circle algorithm.
         * @param center center point of the circle
         * @param radius circle radius in pixels
         * @param color pixel color
         */
        void DrawCircle(const Point& center, int radius, const BackgroundColor& color);
        /**
         * @brief Fill the entire image with the specified color.
         * @param color fill color
         */
        void Fill(const BackgroundColor& color);
        /**
         * @brief Return width of image
         * @return int
         */
        int GetWidth() const;
        /**
         * @brief Return height of image
         * @return int
         */
        int GetHeight() const;
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
        /**
         * @brief Check if point is inside image boundaries
         *
         * @param point
         * @return true
         * @return false
         */
        bool In(const Point& point) const;
    };
}
#endif