#ifndef PRO_MENU_ITEM_EDIT_H
#define PRO_MENU_ITEM_EDIT_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class Menu;
class MenuItemEdit;

class MenuItemEditInterface {

public:
    virtual void init(MenuItemEdit &item) = 0;
    virtual void save(MenuItemEdit &item) = 0;
    virtual void cancel(MenuItemEdit &item) = 0;
};

class MenuItemEdit: public MenuItem, public Menu {

public:
    MenuItemEdit(int id, char *name, char *prefix);
    
    virtual bool select();
    virtual bool exit();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

protected:
    virtual MenuItemEditInterface& getInterface() = 0;
    
};

};

#endif /* PRO_MENU_ITEM_EDIT_H */
