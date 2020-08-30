#include "ProMenuScreen.h"
#include "ProMenuDisplay.h"
#include "ProMenuManager.h"
#include "ProMenuDefs.h"
#include "ProMenuUtils.h"

namespace promenu {

MenuScreen::MenuScreen(char *name):
    MenuBase(name),
    scrollHeaderLine()
{

}

void MenuScreen::begin(MenuManager *manager, int pos)
{
    this->MenuBase::begin(manager, pos);

    this->redraw();
    this->scrollHeaderLine.reset();
}

void MenuScreen::redraw()
{
    this->scrollHeaderLine.setRedraw(true);
}

bool MenuScreen::enter()
{
    return true;
}

void MenuScreen::reset()
{
    this->scrollHeaderLine.reset();
    this->redraw();
}

void MenuScreen::renderHeaderLine(DisplayInterface &display)
{
    char line[display.getWidth() + 1];

    if (display.getHeight() > 1) {
        strlcpy(line, &this->name[this->scrollHeaderLine.getPosition()], sizeof(line));
        utils::rightPaddingText(line, sizeof(line), ' ');
        display.setText(0, 0, line);
    }
}

void MenuScreen::render(DisplayInterface &display)
{
    if (this->scrollHeaderLine.isRedraw()) {
        this->scrollHeaderLine.setRedraw(false);
        this->renderHeaderLine(display);
    }
}

void MenuScreen::process()
{
    int xMax;
    int lineLength;

    if (this->getMenuManager().getDisplay().getHeight() < 2)
        return;

    xMax = this->getMenuManager().getDisplay().getWidth();
    lineLength = strlen(this->name);

    this->scrollHeaderLine.scroll(lineLength, xMax);
}

};