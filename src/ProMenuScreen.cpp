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

int MenuScreen::getRenderHeader(char *text, int maxSize)
{
    if (text)
        strlcpy(text, this->name, maxSize);
    return strlen(this->name);
}

void MenuScreen::renderHeaderLine(DisplayInterface &display)
{
    if (display.getHeight() < 2)
        return;

    char text[display.getWidth() + 1];
   
    int textFullLength = this->getRenderHeader(NULL, sizeof(text));
    char line[textFullLength + 1];

    this->getRenderHeader(line, sizeof(line));
    strlcpy(text, &line[this->scrollHeaderLine.getPosition()], sizeof(text));
    utils::rightPaddingText(text, sizeof(text), ' ');
    display.setText(0, 0, text);
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
    lineLength = this->getRenderHeader(NULL, 0);

    this->scrollHeaderLine.scroll(lineLength, xMax);
}

};