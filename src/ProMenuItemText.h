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
    virtual void save(MenuItemText &item) = 0;
    virtual void cancel(MenuItemText &item) = 0;
};

class MenuItemText: public MenuItem, public Menu {

public:
    MenuItemText(int id, char *name, MenuItemTextInterface &interface, char *prefix = MenuItemText::PREFIX);
    
    virtual bool select();

    virtual bool prev();
    virtual bool next();
    virtual bool exit();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

private:
    MenuItemTextInterface &interface;

    int startPos;
    int cursorPos;
    bool editMode;

    static constexpr char *PREFIX = "$";
};

};

#endif /* PRO_MENU_ITEM_TEXT_H */
