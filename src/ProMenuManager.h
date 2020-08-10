#ifndef PRO_MENU_MANAGER_H
#define PRO_MENU_MANAGER_H

#include "ProMenuDefs.h"
#include "ProMenuDisplay.h"

namespace promenu {

class Menu;

class MenuManager {

public:
    MenuManager(DisplayInterface &display):
        display(display),
        currentMenu(NULL) {};

    void begin(Menu *menu);

    bool up();
    bool down();
    bool back();
    bool select();

    void process();

    Menu* getCurrentMenu() { return this->currentMenu; };
    DisplayInterface& getDisplay() { return this->display; };

    void enterToMenu(Menu *menu);
    void backToMenu(Menu *menu);

    void update();

private:
    MenuManager() = delete;
    MenuManager(const MenuManager&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;

    DisplayInterface &display;
    Menu *currentMenu;
};

};

#endif /* PRO_MENU_MANAGER_H */
