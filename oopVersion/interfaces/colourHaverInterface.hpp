#pragma once

#include "../colour.hpp"

class ColourHaverInterface
{
public:
    virtual const Colour& getColour() const = 0;
    virtual void setColour(const Colour& newColour) = 0;
};
