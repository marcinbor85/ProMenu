#include "ProMenuScreen.h"

#include "ProMenuDefs.h"

namespace promenu {

MenuScreen::MenuScreen(char *name):
    MenuBase(name)
{

}

void MenuScreen::begin(MenuManager *manager, int pos)
{
    this->MenuBase::begin(manager, pos);

    this->redraw();
    this->resetScroll();
}

void MenuScreen::redraw()
{
    this->redrawScroll = true;
}

bool MenuScreen::enter()
{
    this->resetScroll();
    return true;
}

void MenuScreen::reset()
{
    this->resetScroll();
    this->redraw();
}

void MenuScreen::render(DisplayInterface &display)
{
    if (this->redrawScroll) {
        this->redrawScroll = false;
        this->renderScroll(display);
    }
}

void MenuScreen::resetScroll()
{
    this->scrollPos = 0;
    this->redrawScroll = true;
    this->scrollTimeout = MenuScreen::SCROLL_START_TIMEOUT;
    this->lastScrollTick = getTickValue();
}

void MenuScreen::scroll(int lineLength, int xMax)
{
    int lastScrollPos;
    
    if (getTickValue() - this->lastScrollTick < this->scrollTimeout)
        return;
    this->lastScrollTick = getTickValue();

    lastScrollPos = this->scrollPos;
    this->scrollPos++;
    
    if (lineLength - this->scrollPos < xMax) {
        this->scrollPos = 0;
    }

    if ((this->scrollPos == 0) || (lineLength - this->scrollPos <= xMax)) {
        this->scrollTimeout = MenuScreen::SCROLL_START_TIMEOUT;
    } else {
        this->scrollTimeout = MenuScreen::SCROLL_TIMEOUT;
    }

    if (lastScrollPos != this->scrollPos) {
        this->redrawScroll = true;
    }
}

};