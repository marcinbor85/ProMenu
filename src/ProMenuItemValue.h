#ifndef PRO_MENU_ITEM_VALUE_H
#define PRO_MENU_ITEM_VALUE_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class Menu;
template <class T> class MenuItemValue;

template <class T>
class MenuItemValueInterface {

public:
    virtual void init(MenuItemValue<T> &item);
    virtual T getMin(MenuItemValue<T> &item) = 0;
    virtual T getMax(MenuItemValue<T> &item) = 0;
    virtual void setValue(MenuItemValue<T> &item, T value) = 0;
    virtual T getValue(MenuItemValue<T> &item) = 0;
    virtual bool save(MenuItemValue<T> &item) = 0;
    virtual void cancel(MenuItemValue<T> &item) = 0;
};

template <class T>
class MenuItemValue: public MenuItem, public Menu {

public:
    MenuItemValue(int id, char *name, MenuItemValueInterface<T> &interface);
    
    virtual bool select();
    virtual void getRenderName(char *text, int maxSize);
    virtual void getCustomText(int y, char *text, int maxSize);

    virtual bool prev();
    virtual bool next();
    virtual bool exit();
    virtual bool enter();

private:
    MenuItemValueInterface<T> &interface;
};

};

#endif /* PRO_MENU_ITEM_VALUE_H */
