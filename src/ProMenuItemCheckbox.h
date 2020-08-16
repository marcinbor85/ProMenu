#ifndef PRO_MENU_ITEM_CHECKBOX_H
#define PRO_MENU_ITEM_CHECKBOX_H

#include "ProMenuItem.h"

namespace promenu {

class MenuManager;
class MenuItemCheckbox;

class MenuItemCheckboxInterface {

public:
    virtual void setSelected(MenuItemCheckbox &item, bool value) = 0;
    virtual bool isSelected(MenuItemCheckbox &item) = 0;
};

class MenuItemCheckbox: public MenuItem {

public:
    MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface);
    
    virtual bool select();
    virtual int getRenderName(char *text, int maxSize);

private:
    MenuItemCheckboxInterface &interface;
};

};

#endif /* PRO_MENU_ITEM_CHECKBOX_H */
