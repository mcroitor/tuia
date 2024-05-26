#ifndef _USM_GRAPHICS_COLOR_HPP_
#define _USM_GRAPHICS_COLOR_HPP_

#include <cstdint>
#include <iostream>
#include <string>

namespace usm::graphics
{
    enum class ColorType {
        Black = 0x00000000,
        Red = 0x00FF0000,
        Green = 0x0000FF00,
        Blue = 0x000000FF,
        White = 0x00FFFFFF,
    };
  
    /**
     * @brief Color RGB representation
     *
     */
    class Color
    {
    public:
    
        /**
         * @brief Extract the Red channel from the color
         *
         * @param uint32_t color
         * @return uint32_t
         */
        static uint32_t ExtractRed(uint32_t color);
    
        /**
         * @brief Extract the Green channel from the color
         *
         * @param color
         * @return uint32_t
         */
        static uint32_t ExtractGreen(uint32_t color);
    
        /**
         * @brief Extract the Blue channel from the color
         *
         * @param color
         * @return uint32_t
         */
        static uint32_t ExtractBlue(uint32_t color);

    private:
        uint32_t _value;

    public:
    
        /**
         * @brief Construct a new Color object
         *
         */
        Color();
    
        /**
         * @brief Construct a new Color object
         * 
         * @param value 
         */
        Color(uint32_t value);
    
        /**
         * @brief Construct a new Color object
         * 
         * @param color 
         */
        Color(const Color &color);
    
        /**
         * @brief Construct a new Color object
         * 
         * @param red 
         * @param green 
         * @param blue 
         */
        Color(uint8_t red, uint8_t green, uint8_t blue);
    
        /**
         * @brief copy operator
         * 
         * @param color 
         * @return Color 
         */
        Color operator=(const Color &color);
    
        /**
         * @brief compare operator
         * 
         * @param color 
         * @return true 
         * @return false 
         */
        bool operator==(const Color &color) const;

        /**
         * @brief Get red channel
         * 
         * @return uint32_t 
         */
        uint32_t Red() const;
    
        /**
         * @brief Get green channel
         * 
         * @return uint32_t 
         */
        uint32_t Green() const;
    
        /**
         * @brief Get blue channel
         * 
         * @return uint32_t 
         */
        uint32_t Blue() const;
    
        /**
         * @brief Get color value
         * 
         * @return uint32_t 
         */
        uint32_t Value() const;
        /**
         * @brief try to convert Color to the ASCII compatible.
         * @return Color with Red, Green and Blue channels rounded to the 0, 85, 170, 255 values
        */
        Color ToTerminal() const;
        /**
         * @brief return string reprezentation of colors (as HEX)
         * @return std::string
         */
        std::string ToString() const;
    };

    /**
     * @brief read color from input stream
     * 
     * @param in 
     * @param color 
     * @return std::istream& 
     */
    std::istream &operator>>(std::istream &in, Color &color);

    /**
     * @brief write color to output stream
     * 
     * @param out 
     * @param color 
     * @return std::ostream& 
     */
    std::ostream &operator<<(std::ostream &out, const Color &color);

    bool operator < (const Color& left, const Color& right);
}

#endif