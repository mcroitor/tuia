#include "text_image.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace usm::graphics::terminal
{
    TextImage::TextImage(int width, int height, const Symbol &symbol) : symbols(height, std::vector<Symbol>(width, symbol))
    {
    }

    TextImage::TextImage(const TextImage &image) : symbols(image.symbols)
    {
    }

    int TextImage::GetWidth() const
    {
        return symbols[0].size();
    }

    int TextImage::GetHeight() const
    {
        return symbols.size();
    }

    TextImage::Symbol TextImage::GetSymbol(const Point &point) const
    {
        return symbols[point.GetY()][point.GetX()];
    }

    void TextImage::SetSymbol(const Point &point, const TextImage::Symbol &symbol)
    {
        if (symbols.size() <= point.GetY())
        {
#ifdef DEBUG
            std::cerr << "Y coordinate is out of range: " << point.GetY() << std::endl;
#endif
            return;
        }
        if (symbols[point.GetY()].size() <= point.GetX())
        {
#ifdef DEBUG
            std::cerr << "X coordinate is out of range: " << point.GetX() << std::endl;
#endif
            return;
        }
        symbols[point.GetY()][point.GetX()] = symbol;
    }

    void TextImage::Load(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::vector<std::vector<Symbol>> tmp;
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<Symbol> row(line.size(), ' ');
            for (int i = 0; i < line.size(); ++i)
            {
                row[i] = (Symbol)line[i];
            }
            tmp.push_back(row);
        }

        symbols = tmp;
    }

    void TextImage::Save(const std::string &filename) const
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        for (const auto &row : symbols)
        {
            for (const auto &symbol : row)
            {
                file << (char)symbol;
            }
            file << '\n';
        }
    }

    TextImage TextImage::Clone() const
    {
        return TextImage(*this);
    }
}