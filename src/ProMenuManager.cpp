#include "ProMenuManager.h"

#include "ProMenuDisplay.h"
#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenu.h"

namespace promenu {

MenuManager::MenuManager(DisplayInterface &display):
    display(display),
    currentMenu(NULL)
{

}

void MenuManager::begin(Menu *menu)
{
    this->display.begin();
    this->enterToMenu(*menu);
    this->update();
}

void MenuManager::end()
{
    this->currentMenu = NULL;
    this->display.end();
}

void MenuManager::enterToMenu(Menu &menu)
{
    menu.begin(this);
    this->currentMenu = &menu;
}

void MenuManager::backToMenu(Menu &menu)
{
    this->currentMenu = &menu;
}

void MenuManager::update()
{
    this->needRedraw = true;
}

void MenuManager::redraw()
{
    int posMax = this->currentMenu->getItemsNum() - 1;
    int yMax = this->display.getHeight() - 1;
    int xMax = this->display.getWidth() - 1;
    int startPos = this->currentMenu->getStartPos();
    int currentPos = this->currentMenu->getCurrentPos();

    char text[this->display.getWidth()];

    this->display.clear();

    if (posMax >= 0) {
        for (int y = 0; y <= yMax; y++) {
            int pos = startPos + y;

            if (pos == currentPos)
                this->display.setText(0, y, ">");
            
            if ((y == 0) && (pos > 0))
                this->display.setText(xMax, 0, "\x01");
            
            if ((y == yMax && (pos < posMax)))
                this->display.setText(xMax, yMax, "\x02");

            this->currentMenu->getItem(pos).getRenderName(text, sizeof(text) - 2);
            this->display.setText(1, y, text);

            if (pos >= posMax)
                break;
        }
    } else {
        for (int y = 0; y <= yMax; y++) {
            this->currentMenu->getCustomText(y, text, sizeof(text));
            this->display.setText(0, y, text);
        }
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

bool MenuManager::up(int repeat)
{
    while (repeat-- > 0) this->currentMenu->prev();
    this->update();
}

bool MenuManager::down(int repeat)
{
    while (repeat-- > 0) this->currentMenu->next();
    this->update();
}

bool MenuManager::back()
{
    this->currentMenu->exit();
    this->update();
}

bool MenuManager::select()
{
    this->currentMenu->enter();
    this->update();
}

Menu* MenuManager::getCurrentMenu()
{
    return this->currentMenu;
}

DisplayInterface& MenuManager::getDisplay()
{
    return this->display;
}

};