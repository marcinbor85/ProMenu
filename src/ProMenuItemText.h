#ifndef PRO_MENU_ITEM_TEXT_H
#define PRO_MENU_ITEM_TEXT_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class Menu;
class MenuItemText;

class MenuItemTextInterface {

public:
    virtual void init(MenuItemText &item) = 0;
    virtual void setChar(MenuItemText &item, int p, char ch) = 0;
    virtual char getChar(MenuItemText &item, int p) = 0;
    virtual bool save(MenuItemText &item) = 0;
    virtual void cancel(MenuItemText &item) = 0;
};

class MenuItemText: public MenuItem, public Menu {

public:
    MenuItemText(int id, char *name, MenuItemTextInterface &interface);
    
    virtual bool select();
    virtual void getRenderName(char *text, int maxSize);
    virtual void getCustomText(int y, char *text, int maxSize);

    virtual bool prev();
    virtual bool next();
    virtual bool exit();
    virtual bool enter();

private:
    MenuItemTextInterface &interface;
};

};

#endif /* PRO_MENU_ITEM_TEXT_H */
