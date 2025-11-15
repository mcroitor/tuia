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

    TextImage::TextImage(TextImage&& other) noexcept
        : symbols(std::move(other.symbols)) {}

    TextImage& TextImage::operator=(TextImage&& other) noexcept
    {
        if (this != &other) {
            symbols = std::move(other.symbols);
        }
        return *this;
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
        if (!In(point)) {
            return ' ';
        }
        return symbols[point.GetY()][point.GetX()];
    }

    void TextImage::SetSymbol(const Point &point, const TextImage::Symbol &symbol)
    {
        if (!In(point)) {
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
        TextImage copy(GetWidth(), GetHeight());
        copy.symbols = symbols;
        return copy;
    }

    TextImage TextImage::GetPart(const Point &leftTop, const Point &rightBottom) const
    {
        TextImage part(rightBottom.GetX() - leftTop.GetX(), rightBottom.GetY() - leftTop.GetY());
        for (int y = leftTop.GetY(); y < rightBottom.GetY(); ++y)
        {
            for (int x = leftTop.GetX(); x < rightBottom.GetX(); ++x)
            {
                part.SetSymbol(Point(x - leftTop.GetX(), y - leftTop.GetY()), GetSymbol(Point(x, y)));
            }
        }
        return part;
    }

    void TextImage::SetPart(const Point &leftTop, const TextImage &part)
    {
        for (int y = 0; y < part.GetHeight(); ++y)
        {
            for (int x = 0; x < part.GetWidth(); ++x)
            {
                SetSymbol(Point(leftTop.GetX() + x, leftTop.GetY() + y), part.GetSymbol(Point(x, y)));
            }
        }
    }

    void TextImage::Fill(const Symbol &symbol)
    {
        for (auto &row : symbols)
        {
            std::fill(row.begin(), row.end(), symbol);
        }
    }

    void TextImage::Clear()
    {
        Fill(' ');
    }

    bool TextImage::In(const Point &point) const
    {
        return point.GetX() >= 0 && point.GetX() < GetWidth() && point.GetY() >= 0 && point.GetY() < GetHeight();
    }
}