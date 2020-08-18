#ifndef PRO_MENU_H
#define PRO_MENU_H

#include <stddef.h>

namespace promenu {

class MenuManager;
class MenuItem;
class DisplayInterface;

class Menu {

public:
    Menu(int id, char *name, MenuItem **items, int itemsNum);
    
    virtual void begin(MenuManager *manager, int pos = 0);
    virtual void end();
    virtual void reset();

    virtual bool prev();
    virtual bool next();
    virtual bool exit();
    virtual bool enter();

    virtual void render(DisplayInterface &display);
    virtual void process();

    int getId();
    const char* getName();

    MenuManager& getMenuManager();

protected:
    void resetScroll();
    void scroll(int lineLength, int xMax);
    virtual void redraw();

    int scrollPos;
    bool redrawScroll;

private:
    const int id;
    const char *name;
    MenuItem* const *items;
    const int itemsNum;

    Menu *prevMenu;
    MenuManager *manager;
    int currentPos;
    int startPos;

    unsigned long lastScrollTick;
    unsigned long scrollTimeout;

    bool redrawCursor;
    bool redrawList;
    

    void renderCursor(DisplayInterface &display);
    void renderList(DisplayInterface &display);
    void renderScroll(DisplayInterface &display);

    static constexpr unsigned long SCROLL_START_TIMEOUT = 2000UL;
    static constexpr unsigned long SCROLL_TIMEOUT = 500UL;
};

};

#endif /* PRO_MENU_H */
