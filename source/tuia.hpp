#ifndef _USM_GRAPHICS_TUIA_HPP_
#define _USM_GRAPHICS_TUIA_HPP_

#include <cstdint>
#include <string>
#include "terminal_color.hpp"
#include "image.hpp"
#include "text_image.hpp"
#include "point.hpp"

namespace usm::graphics
{
    using terminal::BackgroundColor;
    using terminal::ForegroundColor;

    class TUIA
    {
        static ForegroundColor _foregroundColor;
        static BackgroundColor _backgroundColor;

        static std::string ColorCode();
        static std::string PointCode(const Point& position);
    public:
        /**
         * @brief Create a string representation (ASCII code) for specified colors.
         * @param ForegroundColor
         * @param BackgroundColor
         * @return std::string
         */
        static std::string ColorCode(ForegroundColor fgColor, BackgroundColor bgColor);
        /**
         * @brief Set initial values for background and foreground colors.
         */
        static void Init();
        /**
         * @brief Set full screen mode.
         */
        static void FullScreen();
        /**
         * @brief Set window size.
         * @param width
         * @param height
         */
        static void SetWindowSize(int width, int height);
        /**
         * @brief Set foreground color for text.
         * @param Color will be converted to the appropiate ForegroundColor
         */
        static void SetForegroundColor(const Color &foregroundColor);
        /**
         * @brief Set background color.
         * @param Color will be converted to the appropiate BackgroundColor
         */
        static void SetBackgroundColor(const Color &backgroundColor);
        /**
         * @brief Set foreground color for text.
         * @param ForegroundColor
         */
        static void SetForegroundColor(const ForegroundColor &foregroundColor);
        /**
         * @brief Set background color.
         * @param BackgroundColor
         */
        static void SetBackgroundColor(const BackgroundColor &backgroundColor);
        /**
         * @brief Get current Foreground Color
         * @return Color
         */
        static Color GetForegroundColor();
        /**
         * @brief Get current Background Color
         * @return Color
         */        
        static Color GetBackgroundColor();
        /**
         * @brief Write a text from specific point of screen.
         * @param position point of screen
         * @param line text for printing
         */
        static void WriteLine(const Point &position, const std::string &line);
        /**
         * @brief Clear line from specific point of screen.
         * @param position point of screen
         * @param nChars number of symbols for clear
         */
        static void ClearLine(const Point &position, int nChars);
        /**
         * @brief Clear block of screen.
         * @param leftTop left top point of screen
         * @param rightBottom right bottom point of screen
         */
        static void ClearBlock(const Point &leftTop, const Point &rightBottom);
        /**
         * @brief Clear block of screen.
         * @param position left top point of screen
         * @param nChars number of symbols
         * @param nLines number of lines
         */
        static void ClearBlock(const Point &position, int nChars, int nLines);
        /**
         * @brief Clear screen.
         */
        static void ClearScreen();
        /**
         * @brief Draw image from specified position.
         * @param position left top point of screen
         * @param image
         */
        static void Draw(const Point &position, const Image &image);
        static void Draw(const Image &image);
        static void Draw(const TextImage &image);
        /**
         * @brief Draw block of screen.
         * @param leftTop left top point of screen
         * @param rightBottom right bottom point of screen
         * @param colorBackground color of background
         */
        static void DrawBlock(const Point &leftTop, int nChars, int nLines, const Color &colorBackground);
        /**
         * @brief Set cursor to the specified point.
         * @param position point of screen
         */
        static void SetCursor(const Point &position);
        /**
         * @brief Get cursor position.
         * @return cursor position
         */
        static Point GetCursor();
        /**
         * @brief Return Screen size as point. X value == width, Y value == height
         * @return Point
         */
        static Point GetScreenSize();
        /**
         * @brief Set a color point on the screen.
         * @param position point on the screen
         * @param color of pixel
         */
        static void PutPoint(const Point& position, const Color& color);
        /**
         * @brief Set a color point on the screen.
         * @param position point on the screen
         * @param color color of the pixel in BackgroundColor format
         */
        static void PutPoint(const Point& position, const BackgroundColor& color);
        /**
         * @brief Reset screen colors. Background to Black, text to White.
        */
        static void ResetColors();
    };
}

#endif