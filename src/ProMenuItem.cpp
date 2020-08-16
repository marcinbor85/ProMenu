#include "ProMenuItem.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItem::MenuItem(int id, char *name):
    id(id),
    name(name),
    menu(NULL)
{

}

bool MenuItem::selectFromMenu(Menu *menu)
{
    this->menu = menu;
    return this->select();
}

int MenuItem::getRenderName(char *text, int maxSize)
{
    char line[strlen(this->name) + 1];
    snprintf(line, sizeof(line), "%s", this->name);
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

Menu* MenuItem::getMenu()
{
    return this->menu;
}

};
