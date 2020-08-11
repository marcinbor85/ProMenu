#ifndef PRO_MENU_ITEM_SUBMENU_H
#define PRO_MENU_ITEM_SUBMENU_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;
class Menu;

class MenuItemSubmenu: public MenuItem {

public:
    MenuItemSubmenu(int id, char *name, Menu &submenu);
    
    virtual void select(MenuManager &manager);
    virtual void getDisplayText(MenuManager &manager, char *text, int maxSize);

private:
    Menu &submenu;
};

};

#endif /* PRO_MENU_ITEM_SUBMENU_H */
