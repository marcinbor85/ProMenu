#ifndef PRO_MENU_ITEM_ACTION_H
#define PRO_MENU_ITEM_ACTION_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;

class MenuItemActionInterface {

public:
    virtual void action(MenuItemCallbackSource &source) = 0;
};

class MenuItemAction: public MenuItem {

public:
    MenuItemAction(int id, char *name, MenuItemActionInterface &interface);

    virtual void select(MenuManager &manager);
    
private:
    MenuItemActionInterface &interface;

};

};

#endif /* PRO_MENU_ITEM_ACTION_H */
