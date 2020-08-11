#include "ProMenuItemCheckbox.h"

#include "ProMenuManager.h"

#include <string.h>

namespace promenu {

MenuItemCheckbox::MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface):
    MenuItem(id, name),
    interface(interface)
{

}

void MenuItemCheckbox::select(MenuManager *manager)
{
    this->interface.setSelected(!this->interface.isSelected());
}

void MenuItemCheckbox::getDisplayText(char *text, int maxSize)
{
    strncpy(text, "[", maxSize);
    strncat(text, (this->interface.isSelected() == false) ? " " : "x", maxSize - 1);
    strncat(text, "]", maxSize - 2);    
    strncat(text, this->getName(), maxSize - 3);
}

};