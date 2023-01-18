#pragma once

class Vector;

class VectorHaverInterface
{
public:
    virtual const Vector& getVector() const = 0;
    virtual void setVector(const Vector& inVector) = 0;
    virtual bool shouldAnimateVector() const = 0;
};
