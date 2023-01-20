#pragma once

#include <cmath>

struct Vector
{
    float x;
    float y;

    Vector scale(float scaleFactor) const
    {
        return Vector{x * scaleFactor, y * scaleFactor};
    }

    Vector add(const Vector& other) const
    {
        return Vector{x + other.x, y + other.y};
    }

    float mag() const
    {
        return sqrt(x*x + y*y);
    }

    void normalise()
    {
        float theMag = mag();
        if (theMag < 0.1)
        {
            return;
        }

        x /= theMag;
        y /= theMag;
    }
};
