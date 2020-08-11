#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

namespace promenu {

class MenuManager;
class MenuItem;

struct MenuItemCallbackSource {
    MenuItem *item;
    MenuManager *manager;
};

class MenuItem {

public:
    MenuItem(int id, char *name);

    virtual void select(MenuManager &manager) = 0;
    virtual void getDisplayText(MenuManager &manager, char *text, int maxSize);

    int getId();
    const char* getName();

private:
    const int id;
    const char *name;
};

};

#endif /* PRO_MENU_ITEM_H */
