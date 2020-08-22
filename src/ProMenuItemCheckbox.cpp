#include "ProMenuItemCheckbox.h"

#include "ProMenuManager.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

void MenuItemCheckboxInterface::cancel(MenuItem &item)
{

}

MenuItemCheckbox::MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface, char *prefix):
    MenuItem(id, name, prefix),
    interface(interface)
{

}

bool MenuItemCheckbox::select()
{
    bool s = this->interface.setSelected(*this, !this->interface.isSelected(*this));
    this->interface.save(*this);
    return s;
}

int MenuItemCheckbox::getRenderName(char *text, int maxSize)
{
    char line[strlen(this->name) + strlen(this->prefix) + 5];
    snprintf(line, sizeof(line), "%s[%c] %s", this->prefix, (this->interface.isSelected(*this) == false) ? ' ' : 'x', this->name);
    if (text)
        strlcpy(text, line, maxSize);
    return strlen(line);
}

};