#ifndef PRO_MENU_ITEM_VALUE_H
#define PRO_MENU_ITEM_VALUE_H

#include "ProMenuItem.h"
#include "ProMenuItemEdit.h"

namespace promenu {

class MenuItemValueInterface: public MenuItemEditInterface {

public:
    virtual bool prevValue(MenuItem &item) = 0;
    virtual bool nextValue(MenuItem &item) = 0;
    virtual void getValueText(MenuItem &item, char *text, int maxSize) = 0;

    virtual bool isPrevValueAvailable(MenuItem &item) = 0;
    virtual bool isNextValueAvailable(MenuItem &item) = 0;
};

class MenuItemValue: public MenuItemEdit {

public:
    MenuItemValue(int id, char *name, MenuItemValueInterface &interface, char *prefix = MenuItemValue::PREFIX);
    
    virtual int getRenderName(char *text, int maxSize);

    virtual bool prev();
    virtual bool next();
    
protected:
    virtual MenuItemEditInterface& getInterface();

    virtual void renderValue(DisplayInterface &display);
    virtual void renderScroll(DisplayInterface &display);

private:
    MenuItemValueInterface &interface;

    static constexpr char *PREFIX = "";
};

};

#endif /* PRO_MENU_ITEM_VALUE_H */
