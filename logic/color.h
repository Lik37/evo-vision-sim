#pragma once

#include <cstdint>
#include <ostream>


class Color
{
    uint8_t hue;

public:
    Color(uint8_t hue);

    uint8_t getHue() const;

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
    bool operator< (const Color& other) const;
    bool operator> (const Color& other) const;
    bool operator<=(const Color& other) const;
    bool operator>=(const Color& other) const;

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
};
std::ostream& operator<<(std::ostream& os, const Color& c);
