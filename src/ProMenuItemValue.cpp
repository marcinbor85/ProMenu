#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
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
    return this->interface.prevValue(*this);
}

bool MenuItemValue::next()
{
    return this->interface.nextValue(*this);
}

void MenuItemValue::render(DisplayInterface &display)
{
    char value[display.getWidth() + 1];
    char line[display.getWidth() + 1];
    int y = 0;
    bool isPrev;
    bool isNext;
    char ch[2] = {0};

    this->MenuItemEdit::render(display);

    if (display.getHeight() > 1)
        y = 1;

    this->interface.getValueText(*this, value, sizeof(value));
    snprintf(line, sizeof(line), ">%s<", value);
    display.setText(0, y, line);

    isPrev = this->interface.isPrevValueAvailable(*this);
    isNext = this->interface.isNextValueAvailable(*this);

    if (isPrev && isNext) {
        ch[0] = display.getArrowUpDown();
        display.setText(display.getWidth() - 1, y, ch);
    } else if (isPrev) {
        ch[0] = display.getArrowUp();
        display.setText(display.getWidth() - 1, y, ch);
    } else if (isNext) {
        ch[0] = display.getArrowDown();
        display.setText(display.getWidth() - 1, y, ch);
    }
}

MenuItemEditInterface& MenuItemValue::getInterface()
{
    return this->interface;
}

};
