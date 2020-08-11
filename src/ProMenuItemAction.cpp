#include "ProMenuItemAction.h"

#include "ProMenuManager.h"
#include "ProMenuDisplay.h"

namespace promenu {

MenuItemAction::MenuItemAction(int id, char *name, Action action):
    MenuItem(id, name),
    action(action)
{

}

void MenuItemAction::select(MenuManager *manager)
{
    int ret;
    ret = this->action(this, manager);
    manager->getDisplay().clear();
}   

};