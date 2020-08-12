#ifndef PRO_MENU_MANAGER_H
#define PRO_MENU_MANAGER_H

#include <stddef.h>

namespace promenu {

class DisplayInterface;
class MenuManager;
class Menu;

class MenuManager {

public:
    MenuManager(DisplayInterface &display);

    void begin(Menu *menu);
    void end();

    bool up(int repeat = 1);
    bool down(int repeat = 1);
    bool back();
    bool select();

    void process();

    Menu* getCurrentMenu();
    DisplayInterface& getDisplay();

    void enterToMenu(Menu &menu);
    void backToMenu(Menu &menu);

private:
    MenuManager() = delete;
    MenuManager(const MenuManager&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;

    DisplayInterface &display;
    Menu *currentMenu;

    void update();
    void redraw();

    bool needRedraw;
};

};

#endif /* PRO_MENU_MANAGER_H */
