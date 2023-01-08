#pragma once

struct Vector
{
    int x;
    int y;

    Vector scale(float scaleFactor) const
    {
        return Vector{static_cast<int>(x * scaleFactor), static_cast<int>(y * scaleFactor)};
    }
};
