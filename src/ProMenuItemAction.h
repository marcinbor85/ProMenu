#ifndef PRO_MENU_ITEM_ACTION_H
#define PRO_MENU_ITEM_ACTION_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;
class Menu;
class MenuItemAction;

class MenuItemActionInterface {

public:
    virtual bool action(MenuItemAction &item) = 0;
};

class MenuItemAction: public MenuItem {

public:
    MenuItemAction(int id, char *name, MenuItemActionInterface &interface, char *prefix = MenuItemAction::PREFIX);

    virtual bool select();
    
private:
    MenuItemActionInterface &interface;

    static constexpr char *PREFIX = "";
};

};

#endif /* PRO_MENU_ITEM_ACTION_H */
