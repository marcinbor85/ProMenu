#include "ProMenuItemCheckbox.h"

#include "ProMenuManager.h"

#include <string.h>

namespace promenu {

MenuItemCheckbox::MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface):
    MenuItem(id, name),
    interface(interface)
{

}

void MenuItemCheckbox::select(MenuManager &manager)
{
    MenuItemCallbackSource source = {this, &manager};

    this->interface.setSelected(source, !this->interface.isSelected(source));
}

void MenuItemCheckbox::getDisplayText(MenuManager &manager, char *text, int maxSize)
{
    MenuItemCallbackSource source = {this, &manager};

    strncpy(text, "[", maxSize);
    strncat(text, (this->interface.isSelected(source) == false) ? " " : "x", maxSize - 1);
    strncat(text, "]", maxSize - 2);    
    strncat(text, this->getName(), maxSize - 3);
}

};