#ifndef PRO_MENU_H
#define PRO_MENU_H

#include <stddef.h>

namespace promenu {

class MenuManager;
class MenuItem;

class Menu {

public:
    Menu(int id, char *name, MenuItem **items, int itemsNum);
    
    void begin(MenuManager *manager, int pos = 0);
    void end();
    void reset();

    bool prev();
    bool next();

    int getItemsNum();
    MenuItem* getItem(int i);
    MenuItem* getCurrentItem();
    int getCurrentPos();
    int getStartPos();
    int getId();
    const char* getName();

private:
    const int id;
    const char *name;
    MenuItem* const *items;
    const int itemsNum;

    Menu *prevMenu;
    MenuManager *manager;
    int currentPos;
    int startPos;
};

};

#endif /* PRO_MENU_H */
