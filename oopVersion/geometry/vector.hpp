#pragma once

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
};
