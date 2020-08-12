#ifndef PRO_MENU_ITEM_ACTION_H
#define PRO_MENU_ITEM_ACTION_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;
class Menu;
class MenuItemAction;

class MenuItemActionInterface {

public:
    virtual void action(MenuItemAction &item) = 0;
};

class MenuItemAction: public MenuItem {

public:
    MenuItemAction(int id, char *name, MenuItemActionInterface &interface);

    virtual bool select();
    
private:
    MenuItemActionInterface &interface;

};

};

#endif /* PRO_MENU_ITEM_ACTION_H */
