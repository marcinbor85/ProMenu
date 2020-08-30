#include "ProMenu.h"

#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenuDisplay.h"
#include "ProMenuDefs.h"
#include "ProMenuUtils.h"
#include "ProMenuScrollLine.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

Menu::Menu(char *name, MenuItem **items, int itemsNum):
    MenuScreen(name),
    scrollSelectedLine(),
    items(items),
    itemsNum(itemsNum),
    currentPos(0),
    startPos(0)
{

}

void Menu::begin(MenuManager *manager, int pos)
{
    this->MenuScreen::begin(manager, pos);
    this->resetScrollSelectedLine();

    if (manager != NULL) {
        this->currentPos = pos;

        int h = this->manager->getDisplay().getHeight();

        if (this->currentPos >= h) {
            this->startPos = this->currentPos - h;
        } else {
            this->startPos = 0;
        }

        for (int i = 0; i < this->itemsNum; i++)
            this->items[i]->preload();
    }
}

bool Menu::prev()
{
    bool ret = false;
    
    if (this->currentPos > 0) {
        this->currentPos --;
        this->resetScrollSelectedLine();
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
        this->resetScrollSelectedLine();
        ret = true;
        this->redrawCursor = true;
    }

    int yStart = this->manager->getDisplay().getHeight();
    
    if (yStart >= 2)
        yStart --;

    if (this->currentPos >= (this->startPos + yStart)) {
        this->startPos++;
        this->redrawList = true;
    }

    return ret;
}

void Menu::redraw()
{
    this->MenuScreen::redraw();
    this->redrawCursor = true;
    this->redrawList = true;
}

bool Menu::enter()
{
    this->MenuScreen::enter();
    this->resetScrollSelectedLine();
    return this->items[this->currentPos]->selectFromMenu(this);
}

void Menu::reset()
{
    this->MenuScreen::reset();
    this->resetScrollSelectedLine();
    this->currentPos = 0;
    this->startPos = 0;
}

void Menu::renderCursor(DisplayInterface &display)
{
    int yMax = display.getHeight() - 1;

    display.hideCursor();
    display.deselectChar();

    int yStart = (display.getHeight() >= 2) ? 1 : 0;

    for (int y = yStart; y <= yMax; y++) {
        int pos = this->startPos + y - yStart;
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

    int yStart = (display.getHeight() >= 2) ? 1 : 0;

    for (int y = yStart; y <= yMax; y++) {
        int pos = this->startPos + y - yStart;

        if (pos <= posMax) {
            if (pos == this->currentPos) {
                int textFullLength = this->items[pos]->getRenderName(NULL, sizeof(text));
                char line[textFullLength + 1];

                this->items[pos]->getRenderName(line, sizeof(line));
                strlcpy(text, &line[this->scrollSelectedLine.getPosition()], sizeof(text));
            } else {
                this->items[pos]->getRenderName(text, sizeof(text));
            }

            utils::rightPaddingText(text, sizeof(text), ' ');
            display.setText(1, y, text);

            if (yMax > yStart) {   
                if ((y == yStart) && (pos > 0)) {
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
            display.printChar(' ');
        }
    }
}

void Menu::renderSelectedLine(DisplayInterface &display)
{
    char text[display.getWidth() - 1];
    int yStart = (display.getHeight() >= 2) ? 1 : 0;
    int y = this->currentPos - this->startPos + yStart;

    int textFullLength = this->items[this->currentPos]->getRenderName(NULL, sizeof(text));
    char line[textFullLength + 1];

    this->items[this->currentPos]->getRenderName(line, sizeof(line));
    strlcpy(text, &line[this->scrollSelectedLine.getPosition()], sizeof(text));

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
        this->scrollSelectedLine.setRedraw(false);
        this->renderList(display);
    }
    if (this->scrollSelectedLine.isRedraw()) {
        this->scrollSelectedLine.setRedraw(false);
        this->renderSelectedLine(display);
    }
    this->MenuScreen::render(display);
}

void Menu::resetScrollSelectedLine()
{
    int prevPos = this->scrollSelectedLine.getPosition();
    this->scrollSelectedLine.reset();
    if (prevPos != this->scrollSelectedLine.getPosition())
        this->redrawList = true;
}

void Menu::process()
{
    int xMax;
    int lineLength;

    xMax = this->getMenuManager().getDisplay().getWidth() - 2;
    lineLength = this->items[this->currentPos]->getRenderName(NULL, xMax);
    
    this->scrollSelectedLine.scroll(lineLength, xMax);

    this->MenuScreen::process();
}

};