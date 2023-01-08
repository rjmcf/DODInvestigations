#pragma once

#include <iostream>

class EasingFunction
{
public:
    virtual float ease(float t) = 0;
};

class NoEase : public EasingFunction
{
public:
    virtual float ease(float t) override { return t; }
};

class EaseIn2Out2 : public EasingFunction
{
public:
    virtual float ease(float t) override 
    {
        std::cout << "Easing 2\n";
        const float t2 = t*t;
        std::cout << "t2: " << t2 << "\n";
        const float tinv = 1.0 - t;
        const float t2inv = 1.0 - tinv * tinv;
        const float out = t2 + t * (t2inv - t2);
        std::cout << out << "\n";
        return out;
    }
};
