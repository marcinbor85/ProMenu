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
    int posCount = this->currentMenu->getItemsNum();
    int yMax = this->display.getHeight();

    this->display.clear();

    for (int y = 0; y < yMax; y++) {
        int pos = this->currentMenu->getStartPos() + y;

        if (pos == this->currentMenu->getCurrentPos())
            this->display.setText(0, y, ">");
        
        if ((y == 0) && (pos > 0))
            this->display.setText(this->display.getWidth() - 1, 0, "\x01");
        
        if ((y == yMax - 1 && (pos < posCount - 1)))
            this->display.setText(this->display.getWidth() - 1, yMax - 1, "\x02");

        this->display.setText(1, y, this->currentMenu->getItem(pos)->getName());

        if (pos >= posCount - 1)
            break;
    }
}

void MenuManager::process()
{

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
    Menu *prev = this->currentMenu->getPrevMenu();
    if (prev != NULL) {
        this->currentMenu->end();
    } else {
        this->currentMenu->reset();
    }
    this->update();
}

bool MenuManager::select()
{
    this->currentMenu->getCurrentItem()->select(this);
    this->update();
}

};