#ifndef PRO_MENU_SCREEN_H
#define PRO_MENU_SCREEN_H

#include <stddef.h>

#include "ProMenuBase.h"

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

protected:
    void scroll(int lineLength, int xMax);

    virtual void resetScroll();
    virtual void renderScroll(DisplayInterface &display) = 0;
    virtual void redraw();

    int scrollPos;
    bool redrawScroll;

private:
    unsigned long lastScrollTick;
    unsigned long scrollTimeout;

    static constexpr unsigned long SCROLL_START_TIMEOUT = 2000UL;
    static constexpr unsigned long SCROLL_TIMEOUT = 500UL;
};

};

#endif /* PRO_MENU_SCREEN_H */
