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
    char line[strlen(this->name) + strlen(this->prefix) + 1];
    snprintf(line, sizeof(line), "%s%s", this->prefix, this->name);
    if (text)
        strlcpy(text, line, maxSize);
    return strlen(line);
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
