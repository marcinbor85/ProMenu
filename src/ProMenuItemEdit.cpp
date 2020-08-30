#include "ProMenuItemEdit.h"

#include "ProMenuManager.h"
#include "ProMenuScreen.h"
#include "ProMenuDisplay.h"
#include "ProMenuUtils.h"
#include "ProMenuScrollLine.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemEdit::MenuItemEdit(int id, char *name, char *prefix):
    MenuItem(id, name, prefix),
    MenuScreen(name)
{

}

void MenuItemEdit::preload()
{
    this->MenuItem::preload();
    this->getInterface().load(*this);    
}

void MenuItemEdit::redraw()
{
    this->MenuScreen::redraw();
    this->redrawValue = true;
}

bool MenuItemEdit::select()
{
    this->parentMenu->getMenuManager().enterToMenu(*this);
    return true;
}

bool MenuItemEdit::exit()
{
    this->getInterface().cancel(*this);
    return this->MenuScreen::exit();
}

bool MenuItemEdit::enter()
{
    this->getInterface().save(*this);
    return this->MenuScreen::exit();
}

void MenuItemEdit::render(DisplayInterface &display)
{
    this->MenuScreen::render(display);
    if (this->redrawValue) {
        this->redrawValue = false;
        this->renderValue(display);
    }
}

};
