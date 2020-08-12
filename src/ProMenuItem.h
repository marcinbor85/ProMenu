#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

namespace promenu {

class MenuManager;
class MenuItem;
class Menu;

class MenuItem {

public:
    MenuItem(int id, char *name);

    virtual bool select() = 0;
    virtual void getRenderName(char *text, int maxSize);

    bool selectFromMenu(Menu *menu);

    int getId();
    const char* getName();

    Menu* getMenu();

protected:
    const int id;
    const char *name;
    Menu *menu;
};

};

#endif /* PRO_MENU_ITEM_H */
