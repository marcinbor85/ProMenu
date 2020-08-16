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
    bool ret = false;
    bool r;
    while (repeat-- > 0) {
        r = this->currentMenu->prev();
        if (r)
            ret = true;
    }
    if (ret)
        this->update();
    return ret;
}

bool MenuManager::down(int repeat)
{
    bool ret = false;
    bool r;
    while (repeat-- > 0) {
        r = this->currentMenu->next();
        if (r)
            ret = true;
    }
    if (ret)
        this->update();
    return ret;
}

bool MenuManager::back(int repeat)
{
    bool ret = false;
    bool r;
    while (repeat-- > 0) {
        r = this->currentMenu->exit();
        if (r)
            ret = true;
    }
    if (ret)
        this->update();
    return ret;
}

bool MenuManager::select(int repeat)
{
     bool ret = false;
    bool r;
    while (repeat-- > 0) {
        r = this->currentMenu->enter();
        if (r)
            ret = true;
    }
    if (ret)
        this->update();
    return ret;
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