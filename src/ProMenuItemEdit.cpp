#include "ProMenuItemEdit.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemEdit::MenuItemEdit(int id, char *name, char *prefix):
    MenuItem(id, name, prefix),
    Menu(id, name, NULL, 0)
{

}

bool MenuItemEdit::select()
{
    this->getInterface().init(*this);
    this->parentMenu->getMenuManager().enterToMenu(*this);
    return true;
}

bool MenuItemEdit::exit()
{
    this->getInterface().cancel(*this);
    return this->Menu::exit();
}

bool MenuItemEdit::enter()
{
    this->getInterface().save(*this);
    return this->Menu::exit();
}

void MenuItemEdit::render(DisplayInterface &display)
{
    char line[display.getWidth() + 1];

    display.clear();

    if (display.getHeight() > 1) {
        strlcpy(line, &this->MenuItem::name[this->scrollPos], sizeof(line));
        display.setText(0, 0, line);
    }
}

void MenuItemEdit::process()
{
    int xMax;
    int lineLength;

    if (this->getMenuManager().getDisplay().getHeight() < 2)
        return;

    xMax = this->getMenuManager().getDisplay().getWidth();
    lineLength = strlen(this->MenuItem::name);

    this->scroll(lineLength, xMax);
}

};
