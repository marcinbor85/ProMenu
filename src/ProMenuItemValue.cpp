#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
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

void MenuItemValue::getRenderName(char *text, int maxSize)
{
    char value[maxSize];

    this->interface.getValueText(*this, value, sizeof(value));

    strncpy(text, "[", maxSize);
    maxSize -= 1;
    strncat(text, value, maxSize);
    maxSize -= strlen(value);
    strncat(text, "] ", maxSize);
    maxSize -= 2;
    strncat(text, this->MenuItem::name, maxSize);    
}

void MenuItemValue::getCustomText(int y, char *text, int maxSize)
{
    char value[maxSize];

    switch (y) {
    case 0:
        strncpy(text, this->MenuItem::name, maxSize);
        break;
    case 1:
        this->interface.getValueText(*this, value, sizeof(value));

        strncpy(text, ">", maxSize);
        maxSize -= 1;
        strncat(text, value, maxSize);
        maxSize -= strlen(value);
        strncat(text, "<", maxSize);
        break;
    default:
        if (maxSize > 0)
            text[0] = 0;
        break;
    }
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
    this->end();
    return true;
}

bool MenuItemValue::enter()
{
    this->interface.save(*this);
    this->end();
    return true;
}

};
