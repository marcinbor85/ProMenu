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
    this->currentMenu->end();
    this->currentMenu = &menu;
}

void MenuManager::update()
{
    this->needRedraw = true;
}

void MenuManager::redraw()
{
    this->currentMenu->render(this->display);
}

void MenuManager::process()
{
    if (this->currentMenu == NULL)
        return;
    
    this->currentMenu->process();

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