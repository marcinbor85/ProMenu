#include "ProMenuItemSubmenu.h"
#include "ProMenu.h"

namespace promenu {

void MenuItemSubmenu::select(MenuManager *manager) {
    manager->enterToMenu(&this->submenu);
}

void MenuItemSubmenu::getDisplayText(char *text, int maxSize) {
    strncpy(text, ":", maxSize);
    strncat(text, this->getName(), maxSize - 1);
}

};