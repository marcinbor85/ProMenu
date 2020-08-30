#include "ProMenuItem.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItem::MenuItem(int id, char *name, char *prefix):
    id(id),
    name(name),
    prefix(prefix),
    parentMenu(NULL)
{

}

void MenuItem::preload()
{
    
}

bool MenuItem::selectFromMenu(MenuBase *menu)
{
    this->parentMenu = menu;
    return this->select();
}

int MenuItem::getRenderName(char *text, int maxSize)
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

    len = snprintf(ptr, size, "%s%s", this->prefix, this->name);
    return len;
}

int MenuItem::getId()
{
    return this->id;
}

const char* MenuItem::getName()
{
    return this->name;
}

};
