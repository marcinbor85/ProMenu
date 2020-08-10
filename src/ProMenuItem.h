#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

#include "ProMenu.h"
#include "ProMenuManager.h"

namespace promenu {

class MenuManager;

class MenuItem {

public:
    MenuItem(int id, char *name):
        id(id),
        name(name) {};
    
    virtual void select(MenuManager *manager) = 0;

    int getId() { return this->id; };
    const char* getName() { return this->name; };

    virtual void getDisplayText(char *text, int maxSize) {
        snprintf(text, maxSize, "%s", this->name);
    }

private:
    const int id;
    const char *name;
};

};

#endif /* PRO_MENU_ITEM_H */
