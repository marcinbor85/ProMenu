#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

namespace promenu {

class MenuManager;
class MenuItem;
class Menu;

class MenuItem {

public:
    MenuItem(int id, char *name, char *prefix);

    virtual bool select() = 0;
    virtual int getRenderName(char *text, int maxSize);

    bool selectFromMenu(Menu *menu);

    int getId();
    const char* getName();

protected:
    const int id;
    const char *name;
    const char *prefix;
    Menu *parentMenu;
};

};

#endif /* PRO_MENU_ITEM_H */
