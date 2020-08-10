#include "ProMenuItemAction.h"

namespace promenu {

void MenuItemAction::select(MenuManager *manager) {
    int ret;
    ret = this->action(this, manager);
    manager->getDisplay().clear();
}   

};