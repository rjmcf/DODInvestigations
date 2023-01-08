#pragma once

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
        const float t2 = t*t;
        const float tinv = 1.0 - t;
        const float t2inv = 1.0 - tinv * tinv;
        return t2 + t * (t2inv - t2);
    }
};
