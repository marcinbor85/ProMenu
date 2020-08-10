#ifndef PRO_MENU_ITEM_ACTION_H
#define PRO_MENU_ITEM_ACTION_H

#include "ProMenuItem.h"
#include "ProMenuManager.h"

namespace promenu {

class MenuItemAction: public MenuItem {

public:
    using Action = int (*)(MenuItem *item, MenuManager *manager);

    MenuItemAction(int id, char *name, Action action):
        MenuItem(id, name),
        action(action) {};

    virtual void select(MenuManager *manager);
    
private:
    Action action;

};

};

#endif /* PRO_MENU_ITEM_ACTION_H */
