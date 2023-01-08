#pragma once

#include "vector.hpp"

struct Point
{
    int x;
    int y;

    Point translate(const Vector& vector) const
    {
        return Point{x + vector.x, y + vector.y};
    }

    Vector to(const Point& other) const
    {
        return Vector{other.x - x, other.y - y};
    }
};
