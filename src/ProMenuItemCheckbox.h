#ifndef PRO_MENU_ITEM_CHECKBOX_H
#define PRO_MENU_ITEM_CHECKBOX_H

#include "ProMenuItem.h"

namespace promenu {

class MenuItem;

class MenuItemCheckboxInterface {

public:
    virtual void setSelected(bool value) = 0;
    virtual bool isSelected() = 0;
};

class MenuItemCheckbox: public MenuItem {

public:
    MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface):
        MenuItem(id, name),
        interface(interface) {};
    
    virtual void select(MenuManager *manager);
    virtual void getDisplayText(char *text, int maxSize);

private:
    MenuItemCheckboxInterface &interface;
};

};

#endif /* PRO_MENU_ITEM_CHECKBOX_H */
