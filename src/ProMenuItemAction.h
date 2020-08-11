#ifndef PRO_MENU_ITEM_ACTION_H
#define PRO_MENU_ITEM_ACTION_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;

class MenuItemAction: public MenuItem {

public:
    using Action = int (*)(MenuItem *item, MenuManager *manager);

    MenuItemAction(int id, char *name, Action action);

    virtual void select(MenuManager *manager);
    
private:
    Action action;

};

};

#endif /* PRO_MENU_ITEM_ACTION_H */
