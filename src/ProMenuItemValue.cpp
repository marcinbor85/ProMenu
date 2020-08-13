#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

MenuItemValue::MenuItemValue(int id, char *name, MenuItemValueInterface &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

bool MenuItemValue::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    return true;
}

void MenuItemValue::getRenderName(char *text, int maxSize)
{
    char value[maxSize];

    this->interface.getValueText(*this, value, sizeof(value));
    snprintf(text, maxSize, "[%s] %s", value, this->MenuItem::name);
}

bool MenuItemValue::prev()
{
    return this->interface.prevValue(*this);
}

bool MenuItemValue::next()
{
    return this->interface.nextValue(*this);
}

bool MenuItemValue::exit()
{
    this->interface.cancel(*this);
    this->end();
    return true;
}

bool MenuItemValue::enter()
{
    this->interface.save(*this);
    this->end();
    return true;
}

void MenuItemValue::render(DisplayInterface &display)
{
    char value[display.getWidth()];
    char line[display.getWidth()];

    display.clear();

    strncpy(line, this->MenuItem::name, sizeof(line));
    display.setText(0, 0, line);

    this->interface.getValueText(*this, value, sizeof(value));
    snprintf(line, sizeof(line), ">%s<", value);
    display.setText(0, 1, line);
}

};
