#include "ProMenuItemSubmenu.h"
#include "ProMenu.h"

namespace promenu {

void MenuItemSubmenu::select(MenuManager *manager) {
    manager->enterToMenu(&this->submenu);
}   

};