#ifndef PRO_MENU_ITEM_TEXT_H
#define PRO_MENU_ITEM_TEXT_H

#include "ProMenuItem.h"
#include "ProMenuItemEdit.h"

namespace promenu {

class MenuItemTextInterface: public MenuItemEditInterface {

public:
    virtual void setChar(MenuItemEdit &item, int p, char ch) = 0;
    virtual char getChar(MenuItemEdit &item, int p) = 0;
};

class MenuItemText: public MenuItemEdit {

public:
    MenuItemText(int id, char *name, MenuItemTextInterface &interface, char *prefix = MenuItemText::PREFIX);
    
    virtual bool select();

    virtual bool prev();
    virtual bool next();
    virtual bool enter();

    virtual void render(DisplayInterface &display);

protected:
    virtual MenuItemEditInterface& getInterface();

private:
    MenuItemTextInterface &interface;

    int startPos;
    int cursorPos;
    bool editMode;

    static constexpr char *PREFIX = "";
};

};

#endif /* PRO_MENU_ITEM_TEXT_H */
