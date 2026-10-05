#pragma once

struct Point {
    int x;
    int y;

    Point(int x, int y);
    Point(int x);
    Point();

    Point operator+(const Point &other) const;

    Point operator-(const Point &other) const;

    void set(int x, int y);
    void move(int dx, int dy);
};
