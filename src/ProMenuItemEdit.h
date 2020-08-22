#ifndef PRO_MENU_ITEM_EDIT_H
#define PRO_MENU_ITEM_EDIT_H

#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

class MenuManager;
class MenuScreen;
class MenuItemEdit;

class MenuItemEditInterface {

public:
    virtual void load(MenuItem &item) = 0;
    virtual void save(MenuItem &item) = 0;
    virtual void cancel(MenuItem &item) = 0;
};

class MenuItemEdit: public MenuItem, public MenuScreen {

public:
    MenuItemEdit(int id, char *name, char *prefix);
    
    virtual void preload();

    virtual bool select();
    virtual bool exit();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

protected:
    virtual MenuItemEditInterface& getInterface() = 0;
    virtual void redraw();

    bool redrawValue;

    virtual void renderValue(DisplayInterface &display) = 0;
    virtual void renderScroll(DisplayInterface &display);
    
};

};

#endif /* PRO_MENU_ITEM_EDIT_H */
