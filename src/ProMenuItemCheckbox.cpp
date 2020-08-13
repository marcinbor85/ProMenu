#include "ProMenuItemCheckbox.h"

#include "ProMenuManager.h"

#include <string.h>
#include <stdio.h>

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
    snprintf(text, maxSize, "[%c] %s", (this->interface.isSelected(*this) == false) ? ' ' : 'x', this->name);
}

};