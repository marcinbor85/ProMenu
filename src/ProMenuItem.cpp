#include "ProMenuItem.h"

#include <string.h>

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

void MenuItem::getRenderName(char *text, int maxSize)
{
    strlcpy(text, this->name, maxSize);
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
