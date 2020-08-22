#ifndef PRO_MENU_MANAGER_H
#define PRO_MENU_MANAGER_H

#include <stddef.h>

namespace promenu {

class DisplayInterface;
class MenuManager;
class MenuBase;

class MenuManagerInterface {
public:
    virtual bool up(int repeat) = 0;
    virtual bool down(int repeat) = 0;
    virtual bool back(int repeat) = 0;
    virtual bool select(int repeat) = 0;
};

class MenuManager: public MenuManagerInterface {

public:
    MenuManager(DisplayInterface &display);

    void begin(MenuBase &menu);
    void end();

    virtual bool up(int repeat = 1);
    virtual bool down(int repeat = 1);
    virtual bool back(int repeat = 1);
    virtual bool select(int repeat = 1);

    void process();

    MenuBase& getCurrentMenu();
    DisplayInterface& getDisplay();

    void enterToMenu(MenuBase &menu);
    void backToMenu(MenuBase &menu);

private:
    MenuManager() = delete;
    MenuManager(const MenuManager&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;

    DisplayInterface &display;
    MenuBase *currentMenu;
};

};

#endif /* PRO_MENU_MANAGER_H */
