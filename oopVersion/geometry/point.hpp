#pragma once

#include "vector.hpp"

struct Point
{
    int x;
    int y;

    Point translate(const Vector& vector) const
    {
        return Point{int(x + vector.x), int(y + vector.y)};
    }

    Vector to(const Point& other) const
    {
        return Vector{float(other.x - x), float(other.y - y)};
    }
};
