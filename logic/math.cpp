#include "math.h"


Point::Point(int x, int y) {
        this->x = x;
        this->y = y;
}
Point::Point(int x) {
    this->x = x;
    y = 0;
}
Point::Point() {}

Point Point::operator+(const Point &other) const {
    return Point(x + other.x, y + other.y);
}
Point Point::operator-(const Point &other) const {
    return Point(x - other.x, y - other.y);
}

void Point::set(int x, int y) {
    this->x = x;
    this->y = y;
}
void Point::move(int dx, int dy) {
    x += dx;
    y += dy;
}
