#ifndef PRO_MENU_H
#define PRO_MENU_H

#include "ProMenuScreen.h"

#include <stddef.h>

namespace promenu {

class MenuManager;
class MenuItem;
class DisplayInterface;

class Menu: public MenuScreen {

public:
    Menu(int id, char *name, MenuItem **items, int itemsNum);
    
    virtual void begin(MenuManager *manager, int pos = 0);
    virtual void reset();

    virtual bool prev();
    virtual bool next();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

protected:
    virtual void resetScroll();
    
    virtual void redraw();
    virtual void renderScroll(DisplayInterface &display);

private:
    MenuItem* const *items;
    const int itemsNum;

    int currentPos;
    int startPos;

    bool redrawCursor;
    bool redrawList;
    
    void renderCursor(DisplayInterface &display);
    void renderList(DisplayInterface &display);
};

};

#endif /* PRO_MENU_H */
