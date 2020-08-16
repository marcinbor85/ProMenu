#include "ProMenuItemSubmenu.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

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

int MenuItemSubmenu::getRenderName(char *text, int maxSize)
{
    char line[strlen(this->name) + 2];
    snprintf(line, sizeof(line), ":%s", this->name);
    if (text)
        strlcpy(text, line, maxSize);
    return strlen(line);
}

};