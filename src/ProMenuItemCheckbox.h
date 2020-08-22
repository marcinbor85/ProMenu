#ifndef PRO_MENU_ITEM_CHECKBOX_H
#define PRO_MENU_ITEM_CHECKBOX_H

#include "ProMenuItem.h"
#include "ProMenuItemEdit.h"

namespace promenu {

class MenuItemCheckboxInterface: public MenuItemEditInterface {

public:
    virtual bool setSelected(MenuItem &item, bool value) = 0;
    virtual bool isSelected(MenuItem &item) = 0;

    virtual void cancel(MenuItem &item);
};

class MenuItemCheckbox: public MenuItem {

public:
    MenuItemCheckbox(int id, char *name, MenuItemCheckboxInterface &interface, char *prefix = MenuItemCheckbox::PREFIX);
    
    virtual void preload();
    
    virtual bool select();
    virtual int getRenderName(char *text, int maxSize);

private:
    MenuItemCheckboxInterface &interface;

    static constexpr char *PREFIX = "";
};

};

#endif /* PRO_MENU_ITEM_CHECKBOX_H */
