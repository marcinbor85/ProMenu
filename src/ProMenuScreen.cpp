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
    this->scrollSelectedLine.reset();
}

void MenuScreen::redraw()
{
    this->scrollSelectedLine.setRedraw(true);
}

bool MenuScreen::enter()
{
    this->scrollSelectedLine.reset();
    return true;
}

void MenuScreen::reset()
{
    this->scrollSelectedLine.reset();
    this->redraw();
}

void MenuScreen::render(DisplayInterface &display)
{
    if (this->scrollSelectedLine.isRedraw()) {
        this->scrollSelectedLine.setRedraw(false);
        this->renderSelectedLine(display);
    }
}

};