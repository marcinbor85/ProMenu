#include "ProMenu.h"

#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenuDisplay.h"

#include <string.h>

namespace promenu {

Menu::Menu(int id, char *name, MenuItem **items, int itemsNum):
    id(id),
    name(name),
    items(items),
    itemsNum(itemsNum),
    currentPos(0),
    startPos(0),
    prevMenu(NULL)
{

}

void Menu::begin(MenuManager *manager, int pos)
{
    this->prevMenu = manager->getCurrentMenu();
    this->manager = manager;
    this->currentPos = pos;

    int h = this->manager->getDisplay().getHeight();

    if (this->currentPos >= h) {
        this->startPos = this->currentPos - h;
    } else {
        this->startPos = 0;
    }
}

void Menu::end()
{
    if (this->prevMenu != NULL) {
        this->manager->backToMenu(*this->prevMenu);
    } else {
        this->reset();
    }
}

bool Menu::prev()
{
    bool ret = false;
    
    if (this->currentPos > 0) {
        this->currentPos --;
        ret = true;
    }

    if (this->currentPos < this->startPos)
        this->startPos--;

    return false;
}

bool Menu::next()
{
    bool ret = false;

    if (this->currentPos < this->itemsNum - 1) {
        this->currentPos ++;
        ret = true;
    }

    if (this->currentPos >= (this->startPos + this->manager->getDisplay().getHeight()))
        this->startPos++;

    return ret;
}

bool Menu::exit()
{
    this->end();
    return true;
}

bool Menu::enter()
{
    return this->getCurrentItem().selectFromMenu(this);
}

void Menu::reset()
{
    this->currentPos = 0;
    this->startPos = 0;
}

int Menu::getItemsNum()
{
    return this->itemsNum;
}

MenuItem& Menu::getItem(int i)
{
    return *this->items[i];
}

MenuItem& Menu::getCurrentItem()
{
    return *this->items[this->currentPos];
}

int Menu::getCurrentPos()
{
    return this->currentPos;
}

int Menu::getStartPos()
{
    return this->startPos;
}

int Menu::getId()
{
    return this->id;
}

const char* Menu::getName()
{
    return this->name;
}

void Menu::getCustomText(int y, char *text, int maxSize)
{
    if (maxSize > 0)
        text[0] = 0;
}

MenuManager& Menu::getMenuManager()
{
    return *this->manager;
}


};