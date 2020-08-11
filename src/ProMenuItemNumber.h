#ifndef PRO_MENU_ITEM_NUMBER_H
#define PRO_MENU_ITEM_NUMBER_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class Menu;

class MenuItemNumber: public MenuItem, public Menu {

public:
    MenuItemNumber(int id, char *name, int minimum, int maximum);
    
    virtual void select(MenuManager &manager);
    virtual void getDisplayText(MenuManager &manager, char *text, int maxSize);

private:
    int minimum;
    int maximum;
};

};

#endif /* PRO_MENU_ITEM_NUMBER_H */
