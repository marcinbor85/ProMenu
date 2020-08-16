#ifndef PRO_MENU_ITEM_VALUE_H
#define PRO_MENU_ITEM_VALUE_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class Menu;
class MenuItemValue;

class MenuItemValueInterface {

public:
    virtual void init(MenuItemValue &item) = 0;
    virtual bool prevValue(MenuItemValue &item) = 0;
    virtual bool nextValue(MenuItemValue &item) = 0;
    virtual void getValueText(MenuItemValue &item, char *text, int maxSize) = 0;
    virtual bool save(MenuItemValue &item) = 0;
    virtual void cancel(MenuItemValue &item) = 0;

    virtual bool isPrevValueAvailable(MenuItemValue &item) = 0;
    virtual bool isNextValueAvailable(MenuItemValue &item) = 0;
};

class MenuItemValue: public MenuItem, public Menu {

public:
    MenuItemValue(int id, char *name, MenuItemValueInterface &interface);
    
    virtual bool select();
    virtual void getRenderName(char *text, int maxSize);

    virtual bool prev();
    virtual bool next();
    virtual bool exit();
    virtual bool enter();

    virtual void render(DisplayInterface &display);

private:
    MenuItemValueInterface &interface;
};

};

#endif /* PRO_MENU_ITEM_VALUE_H */
