#include "ProMenuDisplay.h"

namespace promenu {

DisplayInterface::DisplayInterface(int width, int height):
    width(width),
    height(height)
{

}

void DisplayInterface::begin()
{

}

void DisplayInterface::end()
{

}

int DisplayInterface::getWidth()
{
    return this->width;
}

int DisplayInterface::getHeight()
{
    return this->height;
}

};
