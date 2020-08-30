#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenuUtils.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemValue::MenuItemValue(int id, char *name, MenuItemValueInterface &interface, char *prefix):
    MenuItemEdit(id, name, prefix),
    interface(interface)
{

}

int MenuItemValue::getRenderName(char *text, int maxSize)
{
    char value[maxSize];
    char line[strlen(this->MenuItem::name) + 4 + sizeof(value) + strlen(this->prefix)];

    this->interface.getValueText(*this, value, sizeof(value));

    snprintf(line, sizeof(line), "%s[%s] %s", this->prefix, value, this->MenuItem::name);
    if (text)
        strlcpy(text, line, maxSize);
    return strlen(line);
}

bool MenuItemValue::prev()
{
    bool s = this->interface.prevValue(*this);
    if (s)
        this->redrawValue = true;
    return s;
}

bool MenuItemValue::next()
{
    bool s = this->interface.nextValue(*this);
    if (s)
        this->redrawValue = true;
    return s;
}

void MenuItemValue::renderSelectedLine(DisplayInterface &display)
{
    display.hideCursor();
    display.deselectChar();
    
    this->MenuItemEdit::renderSelectedLine(display);
}

void MenuItemValue::renderValue(DisplayInterface &display)
{
    char value[display.getWidth()];
    char line[display.getWidth()];
    int y = 0;
    bool isPrev;
    bool isNext;
    char ch;

    display.hideCursor();
    display.deselectChar();

    if (display.getHeight() > 1)
        y = 1;

    this->interface.getValueText(*this, value, sizeof(value));
    snprintf(line, sizeof(line), ">%s<", value);
    utils::rightPaddingText(line, sizeof(line), ' ');
    display.setText(0, y, line);

    isPrev = this->interface.isPrevValueAvailable(*this);
    isNext = this->interface.isNextValueAvailable(*this);

    if (isPrev && isNext) {
        ch = display.getArrowUpDown();
    } else if (isPrev) {
        ch = display.getArrowUp();
    } else if (isNext) {
        ch = display.getArrowDown();
    } else {
        ch = ' ';
    }

    display.setChar(display.getWidth() - 1, y, ch);
}

MenuItemEditInterface& MenuItemValue::getInterface()
{
    return this->interface;
}

};
