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
    Menu(char *name, MenuItem **items, int itemsNum);
    
    virtual void begin(MenuManager *manager, int pos = 0);
    virtual void reset();

    virtual bool prev();
    virtual bool next();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

    virtual int getRenderHeader(char *text, int maxSize);

protected:
    virtual void redraw();
    virtual void renderSelectedLine(DisplayInterface &display);

private:
    MenuItem* const *items;
    const int itemsNum;

    int currentPos;
    int startPos;

    bool redrawCursor;
    bool redrawList;
    
    void renderCursor(DisplayInterface &display);
    void renderList(DisplayInterface &display);

    void resetScrollSelectedLine();
    ScrollLine scrollSelectedLine;
};

};

#endif /* PRO_MENU_H */
