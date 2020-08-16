#include "ProMenuItemSubmenu.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemSubmenu::MenuItemSubmenu(int id, char *name, Menu &submenu, char *prefix):
    MenuItem(id, name, prefix),
    submenu(submenu)
{

}

bool MenuItemSubmenu::select()
{
    this->parentMenu->getMenuManager().enterToMenu(this->submenu);
    return true;
}

};