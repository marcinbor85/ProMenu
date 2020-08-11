#include "ProMenuItemAction.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"

namespace promenu {

MenuItemAction::MenuItemAction(int id, char *name, MenuItemActionInterface &interface):
    MenuItem(id, name),
    interface(interface)
{

}

void MenuItemAction::select(MenuManager &manager)
{
    MenuItemCallbackSource source = {this, &manager};

    this->interface.action(source);
}   

};