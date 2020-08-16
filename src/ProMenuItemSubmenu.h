#ifndef PRO_MENU_ITEM_SUBMENU_H
#define PRO_MENU_ITEM_SUBMENU_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;
class Menu;

class MenuItemSubmenu: public MenuItem {

public:
    MenuItemSubmenu(int id, char *name, Menu &submenu, char *prefix = MenuItemSubmenu::PREFIX);
    
    virtual bool select();

private:
    Menu &submenu;
    
    static constexpr char *PREFIX = "";
};

};

#endif /* PRO_MENU_ITEM_SUBMENU_H */
