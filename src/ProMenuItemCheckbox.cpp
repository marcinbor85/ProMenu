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

void MenuItemCheckbox::preload()
{
    this->MenuItem::preload();
    this->interface.load(*this);    
}

bool MenuItemCheckbox::select()
{
    bool s = this->interface.setSelected(*this, !this->interface.isSelected(*this));
    this->interface.save(*this);
    return s;
}

int MenuItemCheckbox::getRenderName(char *text, int maxSize)
{
    char line[1];
    char *ptr;
    int size;
    int len;

    if (text) {
        ptr = text;
        size = maxSize;
    } else {
        ptr = line;
        size = sizeof(line);
    }

    len = snprintf(ptr, size, "%s[%c] %s", this->prefix, (this->interface.isSelected(*this) == false) ? ' ' : 'x', this->name);
    return len;
}

};