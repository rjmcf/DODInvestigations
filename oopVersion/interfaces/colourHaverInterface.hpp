#pragma once

#include "colour.hpp"

class ColourHaverInterface
{
public:
    virtual ~ColourHaverInterface() = default;
    virtual const Colour& getColour() const = 0;
    virtual void setColour(const Colour& newColour) = 0;
    virtual bool shouldAnimateColour() const = 0;
};
