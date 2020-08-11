#include "ProMenuItem.h"

#include <string.h>

namespace promenu {

MenuItem::MenuItem(int id, char *name):
    id(id),
    name(name)
{

}

void MenuItem::getDisplayText(MenuManager &manager, char *text, int maxSize)
{
    strncpy(text, this->name, maxSize);
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
