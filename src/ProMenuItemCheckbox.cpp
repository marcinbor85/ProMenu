#include "ProMenuItemCheckbox.h"

#include "ProMenuManager.h"

#include <string.h>

namespace promenu {

MenuItemCheckbox::MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface):
    MenuItem(id, name),
    interface(interface)
{

}

bool MenuItemCheckbox::select()
{
    this->interface.setSelected(*this, !this->interface.isSelected(*this));
    return true;
}

void MenuItemCheckbox::getRenderName(char *text, int maxSize)
{
    strncpy(text, "[", maxSize);
    strncat(text, (this->interface.isSelected(*this) == false) ? " " : "x", maxSize - 1);
    strncat(text, "]", maxSize - 2);    
    strncat(text, this->getName(), maxSize - 3);
}

};