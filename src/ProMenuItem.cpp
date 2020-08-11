#include "ProMenuItem.h"

#include <string.h>

namespace promenu {

void MenuItem::getDisplayText(char *text, int maxSize)
{
    strncpy(text, this->name, maxSize);
}

MenuItem::MenuItem(int id, char *name):
    id(id),
    name(name)
{

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
