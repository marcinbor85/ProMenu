#include "ProMenuItemNumber.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>

namespace promenu {

MenuItemNumber::MenuItemNumber(int id, char *name, int minimum, int maximum):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    minimum(minimum),
    maximum(maximum)
{

}

void MenuItemNumber::select(MenuManager &manager)
{
    manager.enterToMenu(*this);
}

void MenuItemNumber::getDisplayText(MenuManager &manager, char *text, int maxSize)
{
    strncpy(text, "+", maxSize);
    strncat(text, this->MenuItem::getName(), maxSize - 1);
}

};