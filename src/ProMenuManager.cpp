#include "ProMenuManager.h"

#include "ProMenuDisplay.h"
#include "ProMenuManager.h"
#include "ProMenuItem.h"
#include "ProMenuBase.h"

namespace promenu {

MenuManager::MenuManager(DisplayInterface &display):
    display(display),
    currentMenu(NULL)
{

}

void MenuManager::begin(MenuBase &menu)
{
    this->display.begin();
    this->enterToMenu(menu);
    this->process();
}

void MenuManager::end()
{
    this->currentMenu = NULL;
    this->display.end();
}

void MenuManager::enterToMenu(MenuBase &menu)
{
    menu.begin(this);
    this->currentMenu = &menu;
}

void MenuManager::backToMenu(MenuBase &menu)
{
    this->currentMenu->end();
    this->currentMenu = &menu;
}

void MenuManager::process()
{
    if (this->currentMenu == NULL)
        return;
    
    this->currentMenu->process();
    this->currentMenu->render(this->display);
}

bool MenuManager::up(int repeat)
{
    bool ret = false;
    while (repeat-- > 0) {
        if (this->currentMenu->prev())
            ret = true;
    }
    return ret;
}

bool MenuManager::down(int repeat)
{
    bool ret = false;
    while (repeat-- > 0) {
        if (this->currentMenu->next())
            ret = true;
    }
    return ret;
}

bool MenuManager::back(int repeat)
{
    bool ret = false;
    while (repeat-- > 0) {
        if (this->currentMenu->exit())
            ret = true;
    }
    return ret;
}

bool MenuManager::select(int repeat)
{
    bool ret = false;
    while (repeat-- > 0) {
        if (this->currentMenu->enter())
            ret = true;
    }
    return ret;
}

MenuBase& MenuManager::getCurrentMenu()
{
    return *this->currentMenu;
}

DisplayInterface& MenuManager::getDisplay()
{
    return this->display;
}

};