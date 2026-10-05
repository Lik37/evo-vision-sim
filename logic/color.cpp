#include "color.h"


Color::Color(uint8_t hue) : hue(hue) {}

uint8_t Color::getHue() const { return hue; }

bool Color::operator==(const Color& other) const {
    return hue == other.hue;
}
bool Color::operator!=(const Color& other) const {
    return hue != other.hue;
}
bool Color::operator<(const Color& other) const {
    return hue < other.hue;
}
bool Color::operator>(const Color& other) const {
    return hue > other.hue;
}
bool Color::operator<=(const Color& other) const {
    return hue <= other.hue;
}
bool Color::operator>=(const Color& other) const {
    return hue >= other.hue;
}
Color Color::operator+(const Color& other) const {
    return Color(hue + other.hue);
}
Color Color::operator-(const Color& other) const {
    return Color(hue - other.hue);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << static_cast<int>(c.getHue());
    return os;
}
