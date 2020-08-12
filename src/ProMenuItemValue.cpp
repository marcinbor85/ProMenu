#include "ProMenuItemValue.h"

#include "ProMenuManager.h"
#include "ProMenu.h"

#include <string.h>
#include <stdio.h>

namespace promenu {

template <class T>
MenuItemValue<T>::MenuItemValue(int id, char *name, MenuItemValueInterface<T> &interface):
    MenuItem(id, name),
    Menu(id, name, NULL, 0),
    interface(interface)
{

}

template <class T>
bool MenuItemValue<T>::select()
{
    this->interface.init(*this);
    this->menu->getMenuManager().enterToMenu(*this);
    return true;
}

template <class T>
void MenuItemValue<T>::getRenderName(char *text, int maxSize)
{
    snprintf(text, maxSize, "[%d]%s", this->interface.getValue(*this), this->MenuItem::name);
}

template <class T>
void MenuItemValue<T>::getCustomText(int y, char *text, int maxSize)
{
    switch (y) {
    case 0:
        strncpy(text, this->MenuItem::name, maxSize);
        break;
    case 1:
        snprintf(text, maxSize, "> %d <", this->interface.getValue(*this));
        break;
    default:
        if (maxSize > 0)
            text[0] = 0;
        break;
    }
}

template <class T>
bool MenuItemValue<T>::prev()
{
    T val = this->interface.getValue(*this);
    if (val == this->interface.getMin(*this)) {
        return false;
    }

    this->interface.setValue(*this, val - 1);
    return true;
}

template <class T>
bool MenuItemValue<T>::next()
{
    T val = this->interface.getValue(*this);
    if (val == this->interface.getMax(*this)) {
        return false;
    }

    this->interface.setValue(*this, val + 1);
    return true;
}

template <class T>
bool MenuItemValue<T>::exit()
{
    this->interface.cancel(*this);
    this->end();
}

template <class T>
bool MenuItemValue<T>::enter()
{
    this->interface.save(*this);
    this->end();
}

template class MenuItemValue<int>;

};