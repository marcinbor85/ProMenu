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
    return this->items[this->currentPos]->selectFromMenu(this);
}

void Menu::reset()
{
    this->currentPos = 0;
    this->startPos = 0;
}

int Menu::getId()
{
    return this->id;
}

const char* Menu::getName()
{
    return this->name;
}

MenuManager& Menu::getMenuManager()
{
    return *this->manager;
}

void Menu::render(DisplayInterface &display)
{
    int posMax = this->itemsNum - 1;
    int yMax = display.getHeight() - 1;
    int xMax = display.getWidth() - 1;
    int startPos = this->startPos;
    int currentPos = this->currentPos;

    char text[display.getWidth() - 1];
    char ch[2] = {0};

    display.clear();

    for (int y = 0; y <= yMax; y++) {
        int pos = startPos + y;

        if (pos == currentPos)
            display.setText(0, y, ">");
        
        this->items[pos]->getRenderName(text, sizeof(text));
        display.setText(1, y, text);

        if (yMax > 0) {   
            if ((y == 0) && (pos > 0)) {
                ch[0] = display.getArrowUp();
                display.setText(xMax, 0, ch);
            }
            
            if ((y == yMax && (pos < posMax))) {
                ch[0] = display.getArrowDown();
                display.setText(xMax, yMax, ch);
            }
        } else {
            if ((pos > 0) && (pos < posMax)) {
                ch[0] = display.getArrowUpDown();
                display.setText(xMax, 0, ch);
            } else if (pos > 0) {
                ch[0] = display.getArrowUp();
                display.setText(xMax, 0, ch);
            } else if (pos < posMax) {
                ch[0] = display.getArrowDown();
                display.setText(xMax, 0, ch);
            }
        }

        if (pos >= posMax)
            break;
    }
}

};