#include "ProMenuScrollLine.h"

#include "ProMenuDefs.h"

namespace promenu {

ScrollLine::ScrollLine()
{
    this->reset();
}

void ScrollLine::reset()
{
    this->pos = 0;
    this->timeout = this->SCROLL_START_TIMEOUT;
    this->redraw = true;
    this->lastTick = getTickValue();
}

void ScrollLine::setRedraw(bool state)
{
    this->redraw = state;
}

bool ScrollLine::isRedraw()
{
    return this->redraw;
}

int ScrollLine::getPosition()
{
    return this->pos;
}

void ScrollLine::scroll(int lineLength, int xMax)
{
    int lastPos;
    
    if (getTickValue() - this->lastTick < this->timeout)
        return;
    this->lastTick = getTickValue();

    lastPos = this->pos;
    this->pos++;
    
    if (lineLength - this->pos < xMax) {
        this->pos = 0;
    }

    if ((this->pos == 0) || (lineLength - this->pos <= xMax)) {
        this->timeout = ScrollLine::SCROLL_START_TIMEOUT;
    } else {
        this->timeout = ScrollLine::SCROLL_TIMEOUT;
    }

    if (lastPos != this->pos) {
        this->redraw = true;
    }
}

};