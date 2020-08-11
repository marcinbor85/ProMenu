#include "ProMenuManager.h"
#include "ProMenu.h"
#include "ProMenuItem.h"

namespace promenu {

void MenuManager::begin(Menu *menu)
{
    this->display.begin();
    this->enterToMenu(menu);
    this->update();
}

void MenuManager::end()
{
    this->currentMenu = NULL;
    this->display.end();
}

void MenuManager::enterToMenu(Menu *menu)
{
    menu->begin(this);
    this->currentMenu = menu;
}

void MenuManager::backToMenu(Menu *menu)
{
    this->currentMenu = menu;
}

void MenuManager::update()
{
    this->needRedraw = true;
}

void MenuManager::redraw()
{
    int posCount = this->currentMenu->getItemsNum();
    int yMax = this->display.getHeight() - 1;
    int xMax = this->display.getWidth() - 1;
    int startPos = this->currentMenu->getStartPos();
    int currentPos = this->currentMenu->getCurrentPos();

    char name[xMax];

    this->display.clear();

    for (int y = 0; y <= yMax; y++) {
        int pos = startPos + y;

        if (pos == currentPos)
            this->display.setText(0, y, ">");
        
        if ((y == 0) && (pos > 0))
            this->display.setText(xMax, 0, "\x01");
        
        if ((y == yMax && (pos < posCount - 1)))
            this->display.setText(xMax, yMax, "\x02");

        this->currentMenu->getItem(pos)->getDisplayText(name, sizeof(name));
        this->display.setText(1, y, name);

        if (pos >= posCount - 1)
            break;
    }
}

void MenuManager::process()
{
    if (this->currentMenu == NULL)
        return;

    if (this->needRedraw != false) {
        this->needRedraw = false;
        this->redraw();
    }
}

bool MenuManager::up()
{
    this->currentMenu->prev();
    this->update();
}

bool MenuManager::down()
{
    this->currentMenu->next();
    this->update();
}

bool MenuManager::back()
{
    this->currentMenu->end();
    this->update();
}

bool MenuManager::select()
{
    this->currentMenu->getCurrentItem()->select(this);
    this->update();
}

};