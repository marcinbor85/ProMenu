#include "ProMenuItemAction.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

namespace promenu {

MenuItemAction::MenuItemAction(int id, char *name, MenuItemActionInterface &interface):
    MenuItem(id, name),
    interface(interface)
{

}

bool MenuItemAction::select()
{
    this->interface.action(*this);
    return true;
}   

};