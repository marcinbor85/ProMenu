#include "ProMenuItemSubmenu.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>

namespace promenu {

MenuItemSubmenu::MenuItemSubmenu(int id, char *name, Menu &submenu):
    MenuItem(id, name),
    submenu(submenu)
{

}

void MenuItemSubmenu::select(MenuManager &manager)
{
    manager.enterToMenu(&this->submenu);
}

void MenuItemSubmenu::getDisplayText(MenuManager &manager, char *text, int maxSize)
{
    strncpy(text, ":", maxSize);
    strncat(text, this->getName(), maxSize - 1);
}

};