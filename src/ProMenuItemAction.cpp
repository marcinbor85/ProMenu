#include "ProMenuItemAction.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"
#include "ProMenu.h"

namespace promenu {

MenuItemAction::MenuItemAction(int id, char *name, MenuItemActionInterface &interface, char *prefix):
    MenuItem(id, name, prefix),
    interface(interface)
{

}

bool MenuItemAction::select()
{
    return this->interface.action(*this);
}   

};