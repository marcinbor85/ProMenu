#include "ProMenuItemText.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>

namespace promenu {

MenuItemText::MenuItemText(int id, char *name, MenuItemTextInterface &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

bool MenuItemText::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    return true;
}

void MenuItemText::getRenderName(char *text, int maxSize)
{
    strncpy(text, this->MenuItem::name, maxSize);
    maxSize -= strlen(text);
    strncat(text, "...", maxSize);
}

void MenuItemText::getCustomText(int y, char *text, int maxSize)
{
    char value[maxSize];

    switch (y) {
    case 0:
        strncpy(text, this->MenuItem::name, maxSize);
        break;
    case 1:
        // this->interface.getValueText(*this, value, sizeof(value));

        // strncpy(text, ">", maxSize);
        // maxSize -= 1;
        // strncat(text, value, maxSize);
        // maxSize -= strlen(value);
        // strncat(text, "<", maxSize);
        break;
    default:
        if (maxSize > 0)
            text[0] = 0;
        break;
    }
}

bool MenuItemText::prev()
{
    // return this->interface.prevValue(*this);
}

bool MenuItemText::next()
{
    // return this->interface.nextValue(*this);
}

bool MenuItemText::exit()
{
    this->interface.cancel(*this);
    this->end();
    return true;
}

bool MenuItemText::enter()
{
    this->interface.save(*this);
    this->end();
    return true;
}

};