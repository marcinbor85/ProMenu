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

bool MenuItemSubmenu::select()
{
    this->menu->getMenuManager().enterToMenu(this->submenu);
    return true;
}

void MenuItemSubmenu::getRenderName(char *text, int maxSize)
{
    strncpy(text, ":", maxSize);
    strncat(text, this->name, maxSize - 1);
}

};