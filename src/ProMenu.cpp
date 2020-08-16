#include "ProMenu.h"

#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenuDisplay.h"
#include "ProMenuDefs.h"

#include <string.h>
#include <stdio.h>

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

    this->resetScroll();
}

void Menu::end()
{
    this->reset();
}

bool Menu::prev()
{
    bool ret = false;
    
    if (this->currentPos > 0) {
        this->currentPos --;
        this->resetScroll();
        ret = true;
    }

    if (this->currentPos < this->startPos)
        this->startPos--;

    return ret;
}

bool Menu::next()
{
    bool ret = false;

    if (this->currentPos < this->itemsNum - 1) {
        this->currentPos ++;
        this->resetScroll();
        ret = true;
    }

    if (this->currentPos >= (this->startPos + this->manager->getDisplay().getHeight()))
        this->startPos++;

    return ret;
}

bool Menu::exit()
{
    if (this->prevMenu != NULL) {
        this->prevMenu->resetScroll();
        this->manager->backToMenu(*this->prevMenu);
    } else {
        this->reset();
    }
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
    this->resetScroll();
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

        if (pos == currentPos) {
            display.setText(0, y, ">");

            char line[this->items[pos]->getRenderName(NULL, sizeof(text)) + 1];
            this->items[pos]->getRenderName(line, sizeof(line));
            strlcpy(text, &line[this->scrollPos], sizeof(text));
        } else {
            this->items[pos]->getRenderName(text, sizeof(text));
        }

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

void Menu::resetScroll()
{
    this->scrollPos = 0;
    this->scrollTimeout = Menu::SCROLL_START_TIMEOUT;
    this->lastScrollTick = getTickValue();
}

void Menu::scroll(int lineLength, int xMax)
{
    int lastScrollPos;
    
    if (getTickValue() - this->lastScrollTick < this->scrollTimeout)
        return;
    this->lastScrollTick = getTickValue();

    lastScrollPos = this->scrollPos;
    this->scrollPos++;
    
    if (lineLength - this->scrollPos < xMax) {
        this->scrollPos = 0;
    }

    if ((this->scrollPos == 0) || (lineLength - this->scrollPos <= xMax)) {
        this->scrollTimeout = Menu::SCROLL_START_TIMEOUT;
    } else {
        this->scrollTimeout = Menu::SCROLL_TIMEOUT;
    }

    if (lastScrollPos != this->scrollPos) {
        this->manager->update();
    }
}

void Menu::process()
{
    int xMax;
    int lineLength;

    if ((this->items == NULL) || (this->itemsNum == 0))
        return;
    
    xMax = this->getMenuManager().getDisplay().getWidth() - 2;
    lineLength = this->items[this->currentPos]->getRenderName(NULL, xMax);

    this->scroll(lineLength, xMax);
}

};