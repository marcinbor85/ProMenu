#ifndef PRO_MENU_ITEM_H
#define PRO_MENU_ITEM_H

namespace promenu {

class MenuManager;

class MenuItem {

public:
    MenuItem(int id, char *name);

    virtual void select(MenuManager *manager) = 0;

    int getId();
    const char* getName();

    virtual void getDisplayText(char *text, int maxSize);

private:
    const int id;
    const char *name;
};

};

#endif /* PRO_MENU_ITEM_H */
