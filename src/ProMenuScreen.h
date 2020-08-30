#ifndef PRO_MENU_SCREEN_H
#define PRO_MENU_SCREEN_H

#include <stddef.h>

#include "ProMenuBase.h"
#include "ProMenuScrollLine.h"

namespace promenu {

class MenuManager;
class DisplayInterface;

class MenuScreen: public MenuBase {

public:
    MenuScreen(char *name);

    virtual void begin(MenuManager *manager, int pos);

    virtual void render(DisplayInterface &display);

    virtual bool enter();
    virtual void reset();
    
    virtual void process();

protected:
    virtual void renderHeaderLine(DisplayInterface &display);
    virtual void redraw();

    ScrollLine scrollHeaderLine;

};

};

#endif /* PRO_MENU_SCREEN_H */
