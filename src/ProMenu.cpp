#include "ProMenu.h"

#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenuDisplay.h"
#include "ProMenuDefs.h"
#include "ProMenuUtils.h"

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

    this->redraw();
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
        this->redrawCursor = true;
    }

    if (this->currentPos < this->startPos) {
        this->startPos--;
        this->redrawList = true;
    }

    return ret;
}

bool Menu::next()
{
    bool ret = false;

    if (this->currentPos < this->itemsNum - 1) {
        this->currentPos ++;
        this->resetScroll();
        ret = true;
        this->redrawCursor = true;
    }

    if (this->currentPos >= (this->startPos + this->manager->getDisplay().getHeight())) {
        this->startPos++;
        this->redrawList = true;
    }

    return ret;
}

void Menu::redraw()
{
    this->redrawCursor = true;
    this->redrawList = true;
    this->redrawScroll = true;
}

bool Menu::exit()
{
    if (this->prevMenu != NULL) {
        this->prevMenu->resetScroll();
        this->prevMenu->redraw();
        this->manager->backToMenu(*this->prevMenu);
    } else {
        this->reset();
    }
    return true;   
}

bool Menu::enter()
{
    this->resetScroll();
    return this->items[this->currentPos]->selectFromMenu(this);
}

void Menu::reset()
{
    this->currentPos = 0;
    this->startPos = 0;
    this->resetScroll();
    this->redraw();
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

void Menu::renderCursor(DisplayInterface &display)
{
    int yMax = display.getHeight() - 1;

    display.hideCursor();
    display.deselectChar();

    for (int y = 0; y <= yMax; y++) {
        int pos = this->startPos + y;
        char ch = (pos == this->currentPos) ? '>' : ' ';
        display.setChar(0, y, ch);
    }
}

void Menu::renderList(DisplayInterface &display)
{
    int posMax = this->itemsNum - 1;
    int yMax = display.getHeight() - 1;
    char text[display.getWidth() - 1];
    char ch;

    display.hideCursor();
    display.deselectChar();

    for (int y = 0; y <= yMax; y++) {
        int pos = this->startPos + y;

        if (pos <= posMax) {
            if (pos == this->currentPos) {
                int textFullLength = this->items[pos]->getRenderName(NULL, sizeof(text));
                char line[textFullLength + 1];

                this->items[pos]->getRenderName(line, sizeof(line));
                strlcpy(text, &line[this->scrollPos], sizeof(text));
            } else {
                this->items[pos]->getRenderName(text, sizeof(text));
            }

            utils::rightPaddingText(text, sizeof(text), ' ');
            display.setText(1, y, text);

            if (yMax > 0) {   
                if ((y == 0) && (pos > 0)) {
                    ch = display.getArrowUp();
                } else if ((y == yMax && (pos < posMax))) {
                    ch = display.getArrowDown();
                } else {
                    ch = ' ';
                }
            } else {
                if ((pos > 0) && (pos < posMax)) {
                    ch = display.getArrowUpDown();
                } else if (pos > 0) {
                    ch = display.getArrowUp();
                } else if (pos < posMax) {
                    ch = display.getArrowDown();
                } else {
                    ch = ' ';
                }
            }
            display.setChar(display.getWidth() - 1, y, ch);
        } else {
            memset(text, ' ', sizeof(text));
            text[sizeof(text) - 1] = 0;
            display.setText(1, y, text);
        }
    }
}

void Menu::renderScroll(DisplayInterface &display)
{
    char text[display.getWidth() - 1];
    int y = this->currentPos - this->startPos;

    int textFullLength = this->items[this->currentPos]->getRenderName(NULL, sizeof(text));
    char line[textFullLength + 1];

    this->items[this->currentPos]->getRenderName(line, sizeof(line));
    strlcpy(text, &line[this->scrollPos], sizeof(text));

    display.hideCursor();
    display.deselectChar();

    display.setText(1, y, text);
}

void Menu::render(DisplayInterface &display)
{
    if (this->redrawCursor) {
        this->redrawCursor = false;
        this->renderCursor(display);
    }
    if (this->redrawList) {
        this->redrawList = false;
        this->redrawScroll = false;
        this->renderList(display);
    }
    if (this->redrawScroll) {
        this->redrawScroll = false;
        this->renderScroll(display);
    }
}

void Menu::resetScroll()
{
    int prevPos = this->scrollPos;
    this->scrollPos = 0;
    if (prevPos != this->scrollPos)
        this->redrawList = true;
    this->redrawScroll = true;
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
        this->redrawScroll = true;
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