#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemValue::MenuItemValue(int id, char *name, MenuItemValueInterface &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

bool MenuItemValue::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    return true;
}

int MenuItemValue::getRenderName(char *text, int maxSize)
{
    char value[maxSize];
    char line[strlen(this->MenuItem::name) + 4 + sizeof(value)];

    this->interface.getValueText(*this, value, sizeof(value));

    snprintf(line, sizeof(line), "[%s] %s", value, this->MenuItem::name);
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

bool MenuItemValue::exit()
{
    this->interface.cancel(*this);
    return this->Menu::exit();
}

bool MenuItemValue::enter()
{
    this->interface.save(*this);
    return this->Menu::exit();
}

void MenuItemValue::render(DisplayInterface &display)
{
    char value[display.getWidth() + 1];
    char line[display.getWidth() + 1];
    int y = 0;
    bool isPrev;
    bool isNext;
    char ch[2] = {0};

    display.clear();

    if (display.getHeight() > 1) {
        strlcpy(line, &this->MenuItem::name[this->scrollPos], sizeof(line));
        display.setText(0, 0, line);
        y++;
    }

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

void MenuItemValue::process()
{
    int xMax;
    int lineLength;

    xMax = this->getMenuManager().getDisplay().getWidth();
    lineLength = strlen(this->MenuItem::name);

    this->scroll(lineLength, xMax);
}

};
