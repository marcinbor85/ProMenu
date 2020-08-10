#include "ProMenu.h"
#include "ProMenuManager.h"

namespace promenu {

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
    this->manager->backToMenu(this->prevMenu);
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

void Menu::reset()
{
    this->currentPos = 0;
    this->startPos = 0;
}

};