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
    return this->interface.setSelected(*this, !this->interface.isSelected(*this));
}

int MenuItemCheckbox::getRenderName(char *text, int maxSize)
{
    char line[strlen(this->name) + 5];
    snprintf(line, sizeof(line), "[%c] %s", (this->interface.isSelected(*this) == false) ? ' ' : 'x', this->name);
    if (text)
        strlcpy(text, line, maxSize);
    return strlen(line);
}

};