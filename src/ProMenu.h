#ifndef PRO_MENU_H
#define PRO_MENU_H

#include "ProMenuDefs.h"

namespace promenu {

class MenuItem;
class MenuManager;

class Menu {

public:
    Menu(int id, char *name, MenuItem **items, int itemsNum):
        id(id),
        name(name),
        items(items),
        itemsNum(itemsNum),
        currentPos(0),
        startPos(0),
        prevMenu(NULL) {};
    
    void begin(MenuManager *manager, int pos = 0);
    void end();
    void reset();

    bool prev();
    bool next();

    int getItemsNum() { return this->itemsNum; };
    MenuItem* getItem(int i) { return this->items[i]; };
    MenuItem* getCurrentItem() { return this->items[this->currentPos]; };
    int getCurrentPos() { return this->currentPos; };
    int getStartPos() { return this->startPos; };
    Menu* getPrevMenu() { return this->prevMenu; };

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
