#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

namespace promenu {

class MenuManager;
class MenuItem;
class MenuBase;

class MenuItem {

public:
    MenuItem(int id, char *name, char *prefix);

    virtual void preload();
    virtual bool select() = 0;
    virtual int getRenderName(char *text, int maxSize);

    bool selectFromMenu(MenuBase *menu);

    int getId();
    const char* getName();

protected:
    const int id;
    const char *name;
    const char *prefix;
    MenuBase *parentMenu;
};

};

#endif /* PRO_MENU_ITEM_H */
