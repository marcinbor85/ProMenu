#include "ProMenuItemText.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemText::MenuItemText(int id, char *name, MenuItemTextInterface &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

bool MenuItemText::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    return true;
}

void MenuItemText::getRenderName(char *text, int maxSize)
{
    snprintf(text, maxSize, "%s...", this->MenuItem::name);
}

bool MenuItemText::prev()
{
    // return this->interface.prevValue(*this);
}

bool MenuItemText::next()
{
    // return this->interface.nextValue(*this);
}

bool MenuItemText::exit()
{
    this->interface.cancel(*this);
    this->end();
    return true;
}

bool MenuItemText::enter()
{
    this->interface.save(*this);
    this->end();
    return true;
}

void MenuItemText::render(DisplayInterface &display)
{
    char value[display.getWidth()];
    char line[display.getWidth()];

    display.clear();

    strncpy(line, this->MenuItem::name, sizeof(line));
    display.setText(0, 0, line);

    //this->interface.getValueText(*this, value, sizeof(value));
    strcpy(value, "test");
    snprintf(line, sizeof(line), ">%s<", value);
    display.setText(0, 1, line);
}

};